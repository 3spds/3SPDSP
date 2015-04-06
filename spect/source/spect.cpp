//-----------------------------------------------------------------------------
Spect::Spect()
{
	numOutputs = 2;
	numInputs = 2;


	outBufferL = outBufferR = inBufferL = inBufferR = 0;
	inDWTL = inDWTR = inShiftL = inShiftR = outShiftL = outShiftR = 0;
	inSpectraL = inSpectraR = outSpectraL = outSpectraR = 0;
	synthesisWindow = analysisWindow = 0;
	idleTimer = 0;
	bufferPosition = 0;
	inputTimeL = outputTimeL = 0;
	inputTimeR = outputTimeR = 0;

	paramB = paramC = paramD = 1.0f;
	paramA = 0.0f;
	windowSize = 4096;
	kMaxSizeDWT = 4096;
	kMaxDelSize = sampleRate;
	kSizeDWT = kMaxSizeDWT;
	sizeDWT = kSizeDWT;
	blockSize = sizeDWT >> 3;
	halfSizeDWT = sizeDWT >> 1;
	oneOverBlockSize = 1.0f/(float)blockSize;

	allocateMemory();
	//pwtset(20);
	pi = 4.0f * atanf(1.0f);
	twoPi = 8.0f * atanf(1.0f);

	// make the windows
	initHammingWindows();
	scaleWindows();
	setInitialDelay(sizeDWT);
	setNumInputs(2);		// stereo in
	setNumOutputs(2);		// stereo out
	setBypass(false);
	suspend ();		// flush buffer
}

//-----------------------------------------------------------------------------------------
Spect::~Spect()
{
	freeMemory();
}

bool Spect::allocateMemory()
{
	inBufferL = 0;
	inBufferR = 0;
	inBufferL = (float *) malloc(kMaxSizeDWT*sizeof(float));
	inBufferR = (float *) malloc(kMaxSizeDWT*sizeof(float));
	inDWTL = 0;
	inDWTR = 0;
	inDWTL = (float *) malloc(kMaxSizeDWT*sizeof(float));
	inDWTR = (float *) malloc(kMaxSizeDWT*sizeof(float));
	inShiftL = 0;
	inShiftR = 0;
	inShiftL = (float *) malloc(kMaxSizeDWT*sizeof(float));
	inShiftR = (float *) malloc(kMaxSizeDWT*sizeof(float));
	inSpectraL = 0;
	inSpectraR = 0;
	inSpectraL = (float *) malloc(kMaxSizeDWT*sizeof(float));
	inSpectraR = (float *) malloc(kMaxSizeDWT*sizeof(float));
	outSpectraL = 0;
	outSpectraL = (float *) malloc(kMaxSizeDWT*sizeof(float));
	outSpectraR = 0;
	outSpectraR = (float *) malloc(kMaxSizeDWT*sizeof(float));
	outShiftL = 0;
	outShiftL = (float *) malloc(kMaxSizeDWT*sizeof(float));
	outShiftR = 0;
	outShiftR = (float *) malloc(kMaxSizeDWT*sizeof(float));
	outBufferL = 0;
	outBufferL = (float *) malloc(kMaxSizeDWT*sizeof(float));
	outBufferR = 0;
	outBufferR = (float *) malloc(kMaxSizeDWT*sizeof(float));
	synthesisWindow = 0;
	synthesisWindow = (float *) malloc(kMaxSizeDWT*sizeof(float));
	analysisWindow = 0;
	analysisWindow = (float *) malloc(kMaxSizeDWT*sizeof(float));
	wksp = 0;
	wksp = (float *) malloc(kMaxSizeDWT*sizeof(float));
	dwtInputL = new float[kMaxSizeDWT];
	dwtInputR = new float[kMaxSizeDWT];
	dwtOutputL = new float[kMaxSizeDWT];
	dwtOutputR = new float[kMaxSizeDWT];
	eqs = new float[10];
	dbufsL = new float*[11];
	dbufsR = new float*[11];
	for(int i = 0; i<11; i++)
	{
		dbufsL[i] = new float[kMaxDelSize];
		dbufsR[i] = new float[kMaxDelSize];
	}

	cursorsL = new long[11];
	cursorsR = new long[11];

	sizes = new long[11];

	fbcks = new float[11];

	programs = new DaubProgram[numPrograms];

	for(int i = 0; i<kMaxSizeDWT; i++)
	{
		inBufferL[i] = inBufferR[i] = outBufferL[i] = outBufferR[i] = 0.0f;
		inShiftL[i] = inShiftR[i] = outShiftL[i] = outShiftR[i] = 0.0f;
		inSpectraL[i] = inSpectraR[i] = outSpectraL[i] = outSpectraR[i] = 0.0f;
		wksp[i] = 0.0f;
		dwtInputL[i] = dwtInputR[i] = dwtOutputL[i] = dwtOutputR[i] = 0.0f;
	}
	for(int i = 0; i<11; i++)
	{
		eqs[i] = 1.0f;
	}
	for(int i = 0; i<11; i++)
	{
		for(int j = 0; j<kMaxDelSize; j++)
		{
			dbufsL[i][j] = 0.0f; //initialize delay lines
			dbufsR[i][j] = 0.0f; //initialize delay lines
		}
		sizes[i] = sampleRate; //initialize delay times
		cursorsL[i] = 0; //initialize cursor positions
		cursorsR[i] = 0; //initialize cursor positions
		fbcks[i] = 1.0f; //initialize feedback amounts
	}

	return(true);
}

void Spect::freeMemory()
{
	if(inBufferL != 0) {free(inBufferL); inBufferL = 0; }
	if(inBufferR != 0 ) {free(inBufferR); inBufferR = 0;}
	if(inDWTL != 0 ) {free(inDWTL); inDWTL = 0;}
	if(inDWTR != 0 ) {free(inDWTR); inDWTR = 0;}
	if(outBufferL != 0) {free(outBufferL); outBufferL = 0;}
	if(outBufferR != 0 ) {free(outBufferR); outBufferR = 0;}
	if(inShiftL != 0 ) {free(inShiftL); inShiftL = 0;}
	if(inShiftR != 0 ) {free(inShiftR);inShiftR = 0;}
	if(outShiftL != 0 ) {free(outShiftL);outShiftL = 0;}
	if(outShiftR != 0 ) {free(outShiftR);outShiftR = 0;}
	if(inSpectraL != 0 ) {free(inSpectraL);inSpectraL = 0;}
	if(inSpectraR != 0 ) {free(inSpectraR);inSpectraR = 0;}
	if(outSpectraL != 0 ) {free(outSpectraL);outSpectraL = 0;}
	if(outSpectraR != 0 ) {free(outSpectraR);outSpectraR = 0;}
	if(analysisWindow != 0) {free(analysisWindow); analysisWindow = 0;}
	if(synthesisWindow != 0) {free(synthesisWindow); synthesisWindow = 0;}
	if(wksp != 0) {free(wksp); wksp = 0;}
	delete [] dwtInputL;
	delete [] dwtInputR;
	delete [] dwtOutputL;
	delete [] dwtOutputR;
	delete [] eqs;
	delete [] lens;
	for(int i=0; i<11; i++)
		delete [] dbufsL[i];
	delete [] dbufsL;
	for(int i=0; i<11; i++)
		delete [] dbufsR[i];
	delete [] dbufsR;
	delete [] sizes;
	delete [] cursorsL;
	delete [] cursorsR;
}

void Spect::initHammingWindows(void)
{
	long	index;
	float	a = 0.54f, b	= 0.46f;

	windowSelected = kHamming;

	// a - make two hamming windows
	for (index = 0; index < sizeDWT; index++)
		synthesisWindow[index] = analysisWindow[index] = a - b*cosf(twoPi*index/(sizeDWT - 1));
}

void Spect::initVonHannWindows(void)
{
	long	index;
	float	a = 0.50, b	= 0.40;

	windowSelected = kVonHann;

	// a - make two hamming windows
	for (index = 0; index < sizeDWT; index++)
		synthesisWindow[index] = analysisWindow[index] = a - b*cosf(twoPi*index/(sizeDWT - 1));
}

void Spect::initBlackmanWindows(void)
{
	long	index;
	float	a = 0.42, b	= 0.50, c = 0.08;

	windowSelected = kBlackman;

	// a - make two hamming windows
	for (index = 0; index < sizeDWT; index++)
		synthesisWindow[index] = analysisWindow[index] = a - b*cosf(twoPi*index/(sizeDWT - 1)) + c*cosf(2.0f*twoPi*index/(sizeDWT - 1));

}

void Spect::initKaiserWindows(void)
{

	double	bes, xind, floati;
	long	i;

	windowSelected = kKaiser;

	bes = kaiserIno(6.8);
	xind = (float)(sizeDWT-1)*(sizeDWT-1);

	for (i = 0; i < halfSizeDWT; i++)
	{
		floati = (double)i;
		floati = 4.0 * floati * floati;
		floati = sqrt(1. - floati / xind);
		synthesisWindow[i+halfSizeDWT] = kaiserIno(6.8 * floati);
		analysisWindow[halfSizeDWT - i] = synthesisWindow[halfSizeDWT - i] = analysisWindow[i+halfSizeDWT] = (synthesisWindow[i+halfSizeDWT] /= bes);
	}
	analysisWindow[sizeDWT - 1] = synthesisWindow[sizeDWT - 1] = 0.0;
	analysisWindow[0] = synthesisWindow[0] = 0.0;
}

float	Spect::kaiserIno(float x)
{
	float	y, t, e, de, sde, xi;
	long i;

	y = x / 2.;
	t = 1.e-08;
	e = 1.;
	de = 1.;
	for (i = 1; i <= 25; i++)
	{
		xi = i;
		de = de * y / xi;
		sde = de * de;
		e += sde;
		if (e * t > sde)
			break;
	}
	return(e);
}

void Spect::scaleWindows(void)
{
	long index;
	float max, rat;
	max = synthesisWindow[0];
	rat = 1.0f/max;
	//normalize window
	for(index = 0; index < sizeFFT; index++)
	{
		analysisWindow[index] *= rat;
		synthesisWindow[index] *= rat;
	}
	//rescale
	for(index = 0; index < sizeFFT; index++)
	{
		analysisWindow[index] *= 0.0445;
		synthesisWindow[index] *= 0.0445;
	}
}

void Spect::suspend()
{
	long i;
	for(i = 0; i<kMaxSizeDWT; i++)
	{
		inBufferL[i] = inBufferR[i] = outBufferL[i] = outBufferR[i] = 0.0f;
		inShiftL[i] = inShiftR[i] = outShiftL[i] = outShiftR[i] = 0.0f;
		inSpectraL[i] = inSpectraR[i] = outSpectraL[i] = outSpectraR[i] = 0.0f;
		wksp[i] = 0.0f;
	}
	for(int i = 0; i<11; i++)
	{
		for(int j = 0; j<kMaxDelSize; j++)
		{
			dbufsL[i][j] = 0.0f;
			dbufsR[i][j] = 0.0f;
		}
	}
}

void Spect::resume()
{
	//	wantEvents();
}

bool Spect::setBypass(bool pBypass)
{
	bypass = pBypass;
	return(bypass);
}

void Spect::setDWTSize(long newSize)
{
	log2n = (long)log2f((float)newSize);
	newSize = (long)(powf(2.0f, log2n));
	sizeDWT = newSize;
	blockSize = sizeDWT >> 2;
	halfSizeDWT = sizeDWT >> 1;
	oneOverBlockSize = 1.0f/(float)blockSize;

	suspend();
	switch(windowSelected)
	{
		case kHamming:
			initHammingWindows();
			break;
		case kVonHann:
			initVonHannWindows();
			break;
		case kBlackman:
			initBlackmanWindows();
			break;
		case kKaiser:
			initKaiserWindows();
			break;
	}
	scaleWindows();
}

//------------------------------------------------------------------------

// this will generally be overridden to allow DWT size switching
void Spect::updateDWT()
{
	;
}

//-----------------------------------------------------------------------------------------
void Spect::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames)
{
	long i, framesLeft, processframes;
	float *in1 = inputs[0];
	float *in2 = inputs[1];
	float *out1 = outputs[0];
	float *out2 = outputs[1];

	framesLeft = sampleFrames;
	while (framesLeft > 0)
	{
		// how many frames can we process now
		// with this we insure that we stop on the
		// blockSize boundary
		if(framesLeft+bufferPosition < blockSize)
			processframes = framesLeft;
		else
			processframes = blockSize - bufferPosition;
		// flush out the previous output, copy in the new input...
		memcpy(inBufferL+bufferPosition, in1, processframes*sizeof(float));
		for(i=0; i<processframes; i++)
		{
			// copy the old output into the out buffers
			out1[i] = outBufferL[i+bufferPosition];
		}
		if(true)
		{
			memcpy(inBufferR+bufferPosition, in2, processframes*sizeof(float));
			for(i=0; i<processframes; i++)
				// copy the old output into the out buffers
				out2[i] = outBufferR[i+bufferPosition];

			in2 += processframes;
			out2 += processframes;
		}
		else if(channelMode == kMono2StereoMode)
		{
			for(i=0; i<processframes; i++)
			{
				// copy the old output into the out buffers
				out2[i] = outBufferL[i+bufferPosition];
			}

			out2 += processframes;
		}

		bufferPosition += processframes;
		// if filled a buffer, we process a new block
		if(bufferPosition >= blockSize)
		{
			bufferPosition = 0;
			if(bypass == true)
			{
				memcpy(outBufferL, inBufferL, (blockSize) * sizeof(float));
				if(true)
					memcpy(outBufferR, inBufferR, (blockSize) * sizeof(float));
			}
			else
				processBlock();
		}
		in1 += processframes;
		out1 += processframes;
		framesLeft -= processframes;
	}
    idleTimer+=sampleFrames;
}

void Spect::processBlock()
{
	long	i;
	float	outTemp;
	long	maskFFT;
	long level = 0;

	maskFFT = sizeWin - 1;
	//
	inputTimeL += blockSize;
	inputTimeR += blockSize;
	outputTimeL += blockSize;
	outputTimeR += blockSize;
	inputTimeL = inputTimeL & maskFFT;
	inputTimeR = inputTimeR & maskFFT;
	outputTimeL = outputTimeL & maskFFT;
	outputTimeR = outputTimeR & maskFFT;
	//
	// a - shift output buffer and zero out new location
	memcpy(outBufferL, outBufferL+blockSize, (sizeWin - blockSize) * sizeof(float));
	memset(outBufferL+(sizeWin - blockSize), 0, blockSize * sizeof(float));
	if(true)
	{
		// a - shift output buffer and zero out new location
		memcpy(outBufferR, outBufferR+blockSize, (sizeWin - blockSize) * sizeof(float));
		memset(outBufferR+(sizeWin - blockSize), 0, blockSize * sizeof(float));
	}
	// a - shift current samples in inShift
	memcpy(inShiftL, inShiftL+blockSize, (sizeWin - blockSize) * sizeof(float));
	// a1 - copy the new stuff in
	memcpy(inShiftL+(sizeWin - blockSize), inBufferL, blockSize * sizeof(float));
	// b - window the block in
	for(i = 0; i < sizeWin; i++)
	{
		*(inXformL + inputTimeL) = *(inShiftL + i) * *(analysisWindow + i);
		++inputTimeL;
		inputTimeL = inputTimeL & maskFFT;
	}
	if(true)
	{
		// a - shift current samples in inShift
		memcpy(inShiftR, inShiftR+blockSize, (sizeWin - blockSize) * sizeof(float));
		// a1 - copy the new stuff in
		memcpy(inShiftR+(sizeWin - blockSize), inBufferR, blockSize * sizeof(float));
		// b - window the block in
		for(i = 0; i < sizeWin; i++)
		{
			*(inXformR + inputTimeR) = *(inShiftR + i) * *(analysisWindow + i);
			++inputTimeR;
			inputTimeR = inputTimeR & maskFFT;
		}
	}

	//forward transform: (take FFT of inXformL and place result into inSpectraL)
	//fft(inXformL, inSpectraL, sizeWin);

    //do something...

	//inverse transform: (take IFFT of outSpectraL and place result into outShiftL)
	//iwt1(outSpectraL, outShiftL, sizeDWT, &Spect::ipwt);

	// e - overlap add
	for(i = 0; i < sizeWin; i++)
	{
		outTemp = *(outShiftL + outputTimeL) * *(synthesisWindow + i);
		*(outBufferL+i) += outTemp;
		++outputTimeL;
		outputTimeL = outputTimeL & maskFFT;
	}

	if(true)
	{
		//level = 0;
		//forward transform: (take DWT of inDWTR and place result into inSpectraR)

		//copy wksp contents to output

		//DO SOMETHING TO inSpectraR & copy to outSpectraR... use processSignal();

		//inverse transform: (take IDWT of outSpectraR and place result into outShiftR)

		//copy wksp contents to output

		// e - overlap add
		for(i = 0; i < sizeDWT; i++)
		{
			outTemp = *(outShiftR + outputTimeR) * synthesisWindow[i];
			*(outBufferR+i) += outTemp;
			++outputTimeR;
			outputTimeR = outputTimeR & maskFFT;
		}
	}
}
