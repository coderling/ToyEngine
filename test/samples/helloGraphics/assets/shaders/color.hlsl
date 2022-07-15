//HEAD
//VSEntry:VS_Main
//PSEntry:PS_Main
//SM:6.1
//ENDHEAD

#include "vsoutput.hlsl"


VSOut_POS_COLOR VS_Main(float4 position: POSITION, float color :COLOR)
{
    VSOut_POS_COLOR result;
    result.position = position;
    result.color = color;

    return result;
}

float4 PS_Main(VSOut_POS_COLOR intput) 
{
    return intput.color;
}