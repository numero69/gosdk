#pragma once

namespace CS::Classes
{
class CDVariant;
class CRecvTable;
class CRecvProp;
class CRecvProxyData;

using RecvVarProxy_t = void (*)(const CRecvProxyData *data, void *struct_ptr,
				void *out_ptr);
using ArrayLengthRecvProxy_t = void (*)(void *struct_ptr, int object_id,
					int current_array_length);
using DataTableRecvVarProxy_t = void (*)(const CRecvProp *prop, void **out_ptr,
					 void *data_ptr, int object_id);

enum ESendPropType {
	_int = 0,
	_float,
	_vec,
	_vec_xy,
	_string,
	_array,
	_data_table,
	_int_64,
};
class CDVariant {
    public:
	union {
		float Float;
		long Int;
		char *String;
		void *Data;
		float Vector[3];
		__int64 Int64;
	};
	ESendPropType type;
};
class CRecvProxyData {
    public:
	const CRecvProp *RecvProp;
	CDVariant Value;
	int ElementIndex;
	int ObjectID;
};

class CRecvProp {
    public:
	char *PropName;
	ESendPropType PropType;
	int PropFlags;
	int BufferSize;
	int IsInsideOfArray;
	const void *ExtraDataPtr;
	CRecvProp *ArrayProp;
	ArrayLengthRecvProxy_t ArrLengthProxy;
	RecvVarProxy_t Proxy_t;
	DataTableRecvVarProxy_t DataTableProxy_t;
	CRecvTable *DataTable;
	int Offset;
	int ElementsStride;
	int ElementsCount;
	const char *ParrentArrayPropName;
};

class CRecvTable {
    public:
	CRecvProp *Props;
	int PropsCount;
	void *DecoderPtr;
	char *TableName;
	bool IsInitialized;
	bool IsInMainList;
};
} // namespace CS::Classes