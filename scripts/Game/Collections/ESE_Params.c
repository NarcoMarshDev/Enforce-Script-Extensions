class ESE_BaseParam
{
}

class ESE_BoolParam: ESE_BaseParam 			{bool value; 			void ESE_BoolParam(bool in)						{value = in;}}
class ESE_FloatParam: ESE_BaseParam 		{float value; 			void ESE_FloatParam(float in)					{value = in;}}
class ESE_IntParam: ESE_BaseParam 			{int value; 			void ESE_IntParam(int in)						{value = in;}}
class ESE_ResourceNameParam: ESE_BaseParam 	{ResourceName value; 	void ESE_ResourceNameParam(ResourceName in)		{value = in;}}
class ESE_SharedItemRefParam: ESE_BaseParam {SharedItemRef value; 	void ESE_SharedItemRefParam(SharedItemRef in)	{value = in;}}
class ESE_StringParam: ESE_BaseParam 		{string value; 			void ESE_StringParam(string in)					{value = in;}}
class ESE_TypenameParam: ESE_BaseParam 		{typename value; 		void ESE_TypenameParam(typename in)				{value = in;}}
class ESE_VectorParam: ESE_BaseParam 		{vector value; 			void ESE_VectorParam(vector in)					{value = in;}}
class ESE_ClassParam: ESE_BaseParam 		{Class value; 			void ESE_ClassParam(Class in)					{value = in;}}

ESE_BoolParam 			Param(bool in) 			{return new ESE_BoolParam(in);}
ESE_FloatParam 			Param(float in) 		{return new ESE_FloatParam(in);}
ESE_IntParam 			Param(int in) 			{return new ESE_IntParam(in);}
ESE_ResourceNameParam 	Param(ResourceName in) 	{return new ESE_ResourceNameParam(in);}
ESE_SharedItemRefParam 	Param(SharedItemRef in) {return new ESE_SharedItemRefParam(in);}
ESE_StringParam 		Param(string in) 		{return new ESE_StringParam(in);}
ESE_TypenameParam 		Param(typename in) 		{return new ESE_TypenameParam(in);}
ESE_VectorParam 		Param(vector in) 		{return new ESE_VectorParam(in);}
ESE_ClassParam 			Param(Class in) 		{return new ESE_ClassParam(in);}

bool 					UnParam(ESE_BoolParam in) 			{return in.value;}
float					UnParam(ESE_FloatParam in) 			{return in.value;}
int 					UnParam(ESE_IntParam in) 			{return in.value;}
ResourceName			UnParam(ESE_ResourceNameParam in) 	{return in.value;}
SharedItemRef 			UnParam(ESE_SharedItemRefParam in) 	{return in.value;}
string 					UnParam(ESE_StringParam in) 		{return in.value;}
typename 				UnParam(ESE_TypenameParam in) 		{return in.value;}
vector 					UnParam(ESE_VectorParam in) 		{return in.value;}
Class 					UnParam(ESE_ClassParam in) 			{return in.value;}