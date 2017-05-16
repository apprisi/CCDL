#pragma once

#include <support-common.h>

#ifdef __cplusplus
class Classifier;
#else
typedef void* Classifier;
#endif

#ifdef __cplusplus
extern "C"{
#endif
	struct SoftmaxData{
		int label;
		float conf;
	};

	struct SoftmaxLayerOutput{
		int count;
		SoftmaxData* result;
	};

	struct SoftmaxResult{
		int count;
		SoftmaxLayerOutput* list;
	};

	struct BlobData{
		int count;
		float* list;
		int num;
		int channels;
		int height;
		int width;
	};

	//setDecipherCallback
	const static int type_prototxt = 0;			//ͨ���ص�Ҫ����ܵĲ�����Э������
	const static int type_caffemodel = 1;		//ͨ���ص�Ҫ����ܵĲ�����ģ��Ȩ������

	const static int event_decipher = 0;		//�������¼�Ҫ�����
	const static int event_free = 1;			//�������¼�Ҫ���ͷ�����

	//event_decipherʱ�ص��Ľ��Ҫ��������ָ�룬ָ���һ��4�ֽ������ݳ��ȣ�ʣ��������
	//event_freeʱ�����ؽ��Ϊ0�����ˣ���ʱ��lengthΪ0��dataΪevent_decipher���ص�����ָ��
	typedef void* (__stdcall *DecipherCallback)(int event, int type, const void* data, int length);
	Caffe_API float __stdcall getVersion(DecipherCallback callback);

	Caffe_API void  __stdcall releaseBlobData(BlobData* ptr);
	Caffe_API void  __stdcall releaseSoftmaxResult(SoftmaxResult* ptr);

	Caffe_API Classifier* __stdcall createClassifier(
		const char* prototxt_file,
		const char* caffemodel_file,
		float scale_raw = 1,
		const char* mean_file = 0,
		int num_means = 0,
		float* means = 0,
		int gpu_id = -1);

	Caffe_API Classifier* __stdcall createClassifierByData(
		const void* prototxt_data,
		int prototxt_data_length,
		const void* caffemodel_data,
		int caffemodel_data_length,
		float scale_raw = 1,
		const char* mean_file = 0,
		int num_means = 0,
		float* means = 0,
		int gpu_id = -1);

	Caffe_API void __stdcall releaseClassifier(Classifier* classifier);
	Caffe_API SoftmaxResult* __stdcall predictSoftmax(Classifier*classifier, const void* img, int len, int top_n = 5);
	Caffe_API BlobData* __stdcall extfeature(Classifier*classifier, const void* img, int len, const char* feature_name);

	//��ȡ�����ĳ���
	Caffe_API int __stdcall getFeatureLength(BlobData* feature);

	//���������Ƶ�������
	Caffe_API void __stdcall cpyFeature(void* buffer, BlobData* feature);

	//��ȡ�����ĸ���
	Caffe_API int __stdcall getNumOutlayers(SoftmaxResult* result);

	//��ȡ����������ݸ���
	Caffe_API int __stdcall getLayerNumData(SoftmaxLayerOutput* layer);

	//��ȡ�����label
	Caffe_API int __stdcall getResultLabel(SoftmaxResult* result, int layer, int num);

	//��ȡ��������Ŷ�
	Caffe_API float __stdcall getResultConf(SoftmaxResult* result, int layer, int num);

	//���ǩ���Ƕ������㣬ÿ����ȡsoftmax��ע��buf�ĸ�����getNumOutlayers�õ�����Ŀһ��
	Caffe_API void __stdcall getMultiLabel(SoftmaxResult* result, int* buf);

	//��ȡ��0�������label
	Caffe_API int __stdcall getSingleLabel(SoftmaxResult* result);

	//��ȡ��0����������Ŷ�
	Caffe_API float __stdcall getSingleConf(SoftmaxResult* result);

	//��ȡ������Ĵ���û�д��󷵻�0
	Caffe_API const char* __stdcall getLastErrorMessage();

	Caffe_API void __stdcall enablePrintErrorToConsole();

	Caffe_API void __stdcall disableErrorOutput();
#ifdef __cplusplus
}; 
#endif