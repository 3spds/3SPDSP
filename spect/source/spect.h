

//-------------------------------------------------------------------------------------------------------
class Spect
{
public:
	Spect ();
	~Spect ();

	// Processing
//	virtual void processActual(float **inputs, float **outputs, long sampleframes, bool replacing);
    void processBlock();
	void processDoubleBlock();
	void suspend();
	void resume();
	bool setBypass(bool pBypass);

	//methods
	bool allocateMemory();
	void processSpect();
	void initHammingWindows();
	void initVonHannWindows();
	void initBlackmanWindows();
	void initKaiserWindows();
	float kaiserIno(float x);
	void scaleWindows();
	void freeMemory();
	void setWinSize(long int);
	void updateXform();

protected:
	int numOutputs;
	int numInputs;
	bool bypass;

	//inputs...
	float *inBufferL;
	float *inBufferR;

	//outputs...
	float *outBufferL;
	float *outBufferR;

	//inDWT...
	float *inXformL;
	float *inXformR;

	//outDWT...
	float *outXformL;
	float *outXformR;

	//inShift...
	float *inShiftL;
	float *inShiftR;

	float * xformInputL;
	float * xformInputR;
	float * xformOutputL;
	float * xformOutputR;


	//outShift...
	float *outShiftL;
	float *outShiftR;

	//shared workspace for calculations
	float *wksp;

	//inSpectra...
	float *inSpectraL;
	float *inSpectraR;

	//outSpectra...
	float *outSpectraL;
	float *outSpectraR;

	//delay buffers
	int kMaxDelSize;
	float **dbufsL;
	float **dbufsR;

	//cursors...
	long *cursorsL;
	long *cursorsR;

	//sizes...
	long *sizes;

	//feedbacks...
	float *fbcks;

	//windows...
	float *synthesisWindow;
	float *analysisWindow;

	//timers...
	long idleTimer;
	int bufferPosition;
	int inputTimeL;
	int inputTimeR;
	int outputTimeL;
	int outputTimeR;

	//params
	long windowSize;

	//blocking
	int kMaxSizeWin;
	int sizeWin;
	int kSizeWin;
	int blockSize;
	int halfSizeWin;
	float oneOverBlockSize;
	float log2n;

	//pi
	float pi;
	float twoPi;

};
