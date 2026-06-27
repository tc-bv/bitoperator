#ifndef BITOPERATOR_FFAXTTX
#define BITOPERATOR_FFAXTTX
#ifdef __cplusplus
namespace BitOperator {
#endif
	typedef struct {
		unsigned char* dst;
		uint64_t written;
	} BITWRITER,*PBITWRITER;
	__forceinline PBITWRITER BitWriterInit(void* x) {
		PBITWRITER bw=(PBITWRITER)malloc(sizeof(BITWRITER));
		bw->dst=(unsigned char*)x;
		bw->written=0;
		return bw;
	}
	__forceinline void BitWriterSetPointer(PBITWRITER bw,void* x){
		bw->dst=(unsigned char*)x;
	}
	__forceinline void BitWriterWriteBit(PBITWRITER x,bool bit) {
		if(bit)x->dst[x->written>>3]|=(128u>>(x->written&7));
		else x->dst[x->written>>3]&=~(128u>>(x->written&7));
		x->written++;
	}
	__forceinline void BitWriterWriteBits(PBITWRITER x,bool* bits,unsigned int size) {
		for(unsigned int i=0; i<size; i++) {
			BitWriterWriteBit(x,bits[i]);
		}
	}
	__forceinline void BitWriterSkipBits(PBITWRITER x,uint64_t skipc) {
		x->written+=skipc;
	}
	__forceinline void BitWriterSkipToBits(PBITWRITER x,uint64_t skipc) {
		x->written=skipc;
	}
	__forceinline uint64_t BitWriterWroteBits(PBITWRITER x) {
		return x->written;
	}
	__forceinline uint64_t BitWriterWroteBytes(PBITWRITER x) {
		return (x->written>>3)+(bool)(x->written&7);
	}
	__forceinline void BitWriterRelease(PBITWRITER x) {
		free(x);
	}
	typedef struct {
		const unsigned char* src;
		uint64_t read;
	} BITREADER,*PBITREADER;
	__forceinline PBITREADER BitReaderInit(const void* src) {
		PBITREADER br=(PBITREADER)malloc(sizeof(BITREADER));
		br->read=0;
		br->src=(const unsigned char*)src;
		return br;
	}
	__forceinline void BitReaderSetPointer(PBITREADER br,const void* x){
		br->src=(const unsigned char*)x;
	}
	__forceinline bool BitReaderReadBit(PBITREADER x) {
		bool rst=(bool)(x->src[x->read>>3]&(128u>>(x->read&7)));
		x->read++;
		return rst;
	}
	__forceinline void BitReaderReadBits(PBITREADER x,bool* dst,unsigned int size) {
		for(unsigned int i=0; i<size; i++) {
			dst[i]=BitReaderReadBit(x);
		}
	}
	__forceinline void BitReaderSkipBits(PBITREADER x,uint64_t skipc) {
		x->read+=skipc;
	}
	__forceinline void BitReaderSkipToBits(PBITREADER x,uint64_t skipc) {
		x->read=skipc;
	}
	__forceinline uint64_t BitReaderReadBits(PBITREADER x) {
		return x->read;
	}
	__forceinline uint64_t BitReaderReadBytes(PBITREADER x) {
		return (x->read>>3)+(bool)(x->read&7);
	}
	__forceinline void BitReaderRelease(PBITREADER x) {
		free(x);
	}
#ifdef __cplusplus
}
using namespace BitOperator;
#endif
#endif
