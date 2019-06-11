xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 260;
 -8.57192;16.74982;82.84409;,
 7.05892;16.74982;82.84409;,
 7.95208;16.74982;67.21271;,
 -8.12534;16.74982;67.65929;,
 7.95910;16.74982;53.16947;,
 -8.11832;16.74982;53.61605;,
 24.91890;16.74982;61.40770;,
 24.92590;16.74982;47.36447;,
 34.74796;16.74982;75.69827;,
 47.25274;16.74982;66.76613;,
 39.21430;16.74982;54.26135;,
 52.27744;16.74982;38.74229;,
 65.67537;16.74982;48.79061;,
 74.60697;16.74982;37.06721;,
 60.09288;16.74982;27.29807;,
 39.99570;16.74982;33.15977;,
 60.53242;16.74982;27.44711;,
 48.25120;16.74982;21.86459;,
 63.72112;16.74982;10.27133;,
 81.86458;16.74982;8.87597;,
 82.42240;16.74982;-5.35951;,
 64.27947;16.74982;-5.35951;,
 51.43989;16.74982;-3.96361;,
 59.67868;16.74982;-23.34799;,
 46.83910;16.74982;-21.95263;,
 72.93244;16.74982;-34.10911;,
 65.39620;16.74982;-45.83251;,
 53.39362;16.74982;-36.90037;,
 33.40822;16.74982;-39.07765;,
 38.32114;16.74982;-49.34953;,
 47.25274;16.74982;-66.76669;,
 34.30138;16.74982;-73.46593;,
 24.03006;16.74982;-57.38798;,
 20.01028;16.74982;-48.00979;,
 11.01712;16.74982;-61.56163;,
 6.99736;16.74982;-52.18291;,
 7.95208;16.74982;-82.84411;,
 -9.01850;16.74982;-81.95095;,
 -9.46508;16.74982;-62.30089;,
 -11.69798;16.74982;-50.68927;,
 -23.44190;16.74982;-57.86047;,
 -25.67534;16.74982;-46.24885;,
 -34.02804;16.74982;-74.35910;,
 -47.42600;16.74982;-64.53379;,
 -38.49386;16.74982;-51.58242;,
 -33.58148;16.74982;-39.52423;,
 -51.84212;16.74982;-37.49329;,
 -46.92920;16.74982;-25.43509;,
 -66.62948;16.74982;-47.11663;,
 -75.11502;16.74982;-35.50501;,
 -59.93079;16.74982;-26.57287;,
 -65.34534;16.74982;-6.29101;,
 -52.57490;16.74982;-5.05063;,
 -82.26086;16.74982;-4.68937;,
 -82.26086;16.74982;10.04831;,
 -65.28974;16.74982;9.60173;,
 -52.75095;16.74982;10.94471;,
 -62.61024;16.74982;27.91205;,
 -49.65890;16.74982;24.78599;,
 -74.66846;16.74982;36.84419;,
 -67.07606;16.74982;49.79555;,
 -53.23154;16.74982;41.30999;,
 -41.61990;16.74982;34.61129;,
 -39.34272;16.74982;53.44541;,
 -27.73110;16.74982;46.74671;,
 -47.42600;16.74982;68.55244;,
 -33.13490;16.74982;75.25169;,
 -26.88224;16.74982;62.30033;,
 -8.57192;0.48982;82.84409;,
 -8.12534;0.48982;67.65929;,
 7.95208;0.48982;67.21271;,
 7.05892;0.48982;82.84409;,
 -8.11832;0.48982;53.61605;,
 7.95910;0.48982;53.16947;,
 24.92590;0.48982;47.36447;,
 24.91890;0.48982;61.40770;,
 34.74796;0.48982;75.69827;,
 39.21430;0.48982;54.26135;,
 47.25274;0.48982;66.76613;,
 52.27744;0.48982;38.74229;,
 65.67537;0.48982;48.79061;,
 60.09288;0.48982;27.29807;,
 74.60697;0.48982;37.06721;,
 39.99570;0.48982;33.15977;,
 48.25120;0.48982;21.86459;,
 60.53242;0.48982;27.44711;,
 63.72112;0.48982;10.27133;,
 81.86458;0.48982;8.87597;,
 64.27947;0.48982;-5.35951;,
 82.42240;0.48982;-5.35951;,
 51.43989;0.48982;-3.96361;,
 46.83910;0.48982;-21.95263;,
 59.67868;0.48982;-23.34799;,
 72.93244;0.48982;-34.10911;,
 53.39362;0.48982;-36.90037;,
 65.39620;0.48982;-45.83251;,
 33.40822;0.48982;-39.07765;,
 38.32114;0.48982;-49.34953;,
 47.25274;0.48982;-66.76669;,
 24.03006;0.48982;-57.38798;,
 34.30138;0.48982;-73.46593;,
 20.01028;0.48982;-48.00979;,
 6.99736;0.48982;-52.18291;,
 11.01712;0.48982;-61.56163;,
 7.95208;0.48982;-82.84411;,
 -9.46508;0.48982;-62.30089;,
 -9.01850;0.48982;-81.95095;,
 -11.69798;0.48982;-50.68927;,
 -25.67534;0.48982;-46.24885;,
 -23.44190;0.48982;-57.86047;,
 -34.02804;0.48982;-74.35910;,
 -38.49386;0.48982;-51.58242;,
 -47.42600;0.48982;-64.53379;,
 -33.58148;0.48982;-39.52423;,
 -46.92920;0.48982;-25.43509;,
 -51.84212;0.48982;-37.49329;,
 -66.62948;0.48982;-47.11663;,
 -59.93079;0.48982;-26.57287;,
 -75.11502;0.48982;-35.50501;,
 -52.57490;0.48982;-5.05063;,
 -65.34534;0.48982;-6.29101;,
 -82.26086;0.48982;-4.68937;,
 -65.28974;0.48982;9.60173;,
 -82.26086;0.48982;10.04831;,
 -52.75095;0.48982;10.94471;,
 -62.61024;0.48982;27.91205;,
 -49.65890;0.48982;24.78599;,
 -74.66846;0.48982;36.84419;,
 -53.23154;0.48982;41.30999;,
 -67.07606;0.48982;49.79555;,
 -41.61990;0.48982;34.61129;,
 -27.73110;0.48982;46.74671;,
 -39.34272;0.48982;53.44541;,
 -47.42600;0.48982;68.55244;,
 -26.88224;0.48982;62.30033;,
 -33.13490;0.48982;75.25169;,
 -0.51458;16.74982;18.65483;,
 -0.51458;0.48982;18.65483;,
 -10.07204;0.48982;16.43435;,
 -10.07204;16.74982;16.43435;,
 -17.49650;0.48982;-0.08641;,
 -16.74536;0.48982;-8.38135;,
 -16.74536;16.74982;-8.38135;,
 -17.49650;16.74982;-0.08641;,
 6.88990;0.48982;17.46359;,
 14.70964;0.48982;9.37709;,
 14.70964;16.74982;9.37709;,
 6.88990;16.74982;17.46359;,
 15.95380;0.49222;-4.09861;,
 15.93976;16.74982;-4.11427;,
 9.44248;0.48982;-13.18951;,
 9.44248;16.74982;-13.18951;,
 3.80542;0.48982;-16.75027;,
 3.80542;16.74982;-16.75027;,
 -6.86606;16.74982;-15.23989;,
 -6.86606;0.48982;-15.23989;,
 -17.33666;16.74982;8.47961;,
 -17.33666;0.48982;8.47961;,
 -12.66134;0.48982;20.94173;,
 -12.66134;16.74982;20.94173;,
 -0.72464;0.48982;23.99165;,
 -0.72464;16.74982;23.99165;,
 8.91652;16.74982;21.63347;,
 8.91652;0.48982;21.63347;,
 18.67756;16.75012;11.14613;,
 18.67756;0.49012;11.14613;,
 19.89094;16.75042;-5.03497;,
 19.90498;0.49282;-5.01931;,
 11.92540;16.74982;-15.74317;,
 11.92540;0.48982;-15.74317;,
 4.44532;16.74982;-19.96273;,
 4.44532;0.48982;-19.96273;,
 -8.23442;0.48982;-18.64135;,
 -8.23442;16.74982;-18.64135;,
 -20.36174;0.48982;-10.21249;,
 -20.36174;16.74982;-10.21249;,
 -21.80624;0.48982;10.31453;,
 -21.80624;16.74982;10.31453;,
 -22.50986;16.74982;-0.26569;,
 -22.50986;0.48982;-0.26569;,
 -8.17664;16.31332;-17.84971;,
 6.42766;16.31332;-17.84971;,
 6.42766;16.31332;-51.08617;,
 -8.17664;16.31332;-51.08617;,
 6.42766;16.31332;-17.84971;,
 6.42766;0.92632;-17.84971;,
 6.42766;0.92632;-51.08617;,
 6.42766;16.31332;-51.08617;,
 6.42766;0.92632;-17.84971;,
 -8.17664;0.92632;-17.84971;,
 -8.17664;0.92632;-51.08617;,
 6.42766;0.92632;-51.08617;,
 -8.17664;0.92632;-17.84971;,
 -8.17664;16.31332;-17.84971;,
 -8.17664;16.31332;-51.08617;,
 -8.17664;0.92632;-51.08617;,
 6.42766;16.31332;-17.84971;,
 -8.17664;16.31332;-17.84971;,
 -8.17664;16.31332;-51.08617;,
 6.42766;16.31332;-51.08617;,
 -8.17664;16.31332;52.72505;,
 6.42766;16.31332;52.72505;,
 6.42766;16.31332;19.48859;,
 -8.17664;16.31332;19.48859;,
 6.42766;16.31332;52.72505;,
 6.42766;0.92632;52.72505;,
 6.42766;0.92632;19.48859;,
 6.42766;16.31332;19.48859;,
 6.42766;0.92632;52.72505;,
 -8.17664;0.92632;52.72505;,
 -8.17664;0.92632;19.48859;,
 6.42766;0.92632;19.48859;,
 -8.17664;0.92632;52.72505;,
 -8.17664;16.31332;52.72505;,
 -8.17664;16.31332;19.48859;,
 -8.17664;0.92632;19.48859;,
 6.42766;16.31332;52.72505;,
 -8.17664;16.31332;52.72505;,
 -8.17664;16.31332;19.48859;,
 6.42766;16.31332;19.48859;,
 51.43180;16.31332;10.63961;,
 51.43180;16.31332;-3.96415;,
 18.19534;16.31332;-3.96415;,
 18.19534;16.31332;10.63961;,
 51.43180;16.31332;-3.96415;,
 51.43180;0.92632;-3.96415;,
 18.19534;0.92632;-3.96415;,
 18.19534;16.31332;-3.96415;,
 51.43180;0.92632;-3.96415;,
 51.43180;0.92632;10.63961;,
 18.19534;0.92632;10.63961;,
 18.19534;0.92632;-3.96415;,
 51.43180;0.92632;10.63961;,
 51.43180;16.31332;10.63961;,
 18.19534;16.31332;10.63961;,
 18.19534;0.92632;10.63961;,
 51.43180;16.31332;-3.96415;,
 51.43180;16.31332;10.63961;,
 18.19534;16.31332;10.63961;,
 18.19534;16.31332;-3.96415;,
 -22.18532;16.31332;10.63961;,
 -22.18532;16.31332;-3.96415;,
 -55.42178;16.31332;-3.96415;,
 -55.42178;16.31332;10.63961;,
 -22.18532;16.31332;-3.96415;,
 -22.18532;0.92632;-3.96415;,
 -55.42178;0.92632;-3.96415;,
 -55.42178;16.31332;-3.96415;,
 -22.18532;0.92632;-3.96415;,
 -22.18532;0.92632;10.63961;,
 -55.42178;0.92632;10.63961;,
 -55.42178;0.92632;-3.96415;,
 -22.18532;0.92632;10.63961;,
 -22.18532;16.31332;10.63961;,
 -55.42178;16.31332;10.63961;,
 -55.42178;0.92632;10.63961;,
 -22.18532;16.31332;-3.96415;,
 -22.18532;16.31332;10.63961;,
 -55.42178;16.31332;10.63961;,
 -55.42178;16.31332;-3.96415;;
 
 286;
 4;0,1,2,3;,
 4;2,4,5,3;,
 4;2,6,7,4;,
 4;8,9,10,6;,
 3;7,6,10;,
 3;10,11,7;,
 4;12,13,14,11;,
 3;7,11,15;,
 4;11,16,17,15;,
 3;17,16,18;,
 4;19,20,21,18;,
 3;17,18,21;,
 3;21,22,17;,
 4;21,23,24,22;,
 4;25,26,27,23;,
 3;24,23,27;,
 3;28,24,27;,
 3;28,27,29;,
 4;30,31,32,29;,
 3;29,32,28;,
 3;33,28,32;,
 4;32,34,35,33;,
 4;36,37,38,34;,
 3;34,38,35;,
 3;39,35,38;,
 4;38,40,41,39;,
 4;42,43,44,40;,
 3;41,40,44;,
 3;45,41,44;,
 4;44,46,47,45;,
 4;48,49,50,46;,
 3;47,46,50;,
 4;50,51,52,47;,
 4;53,54,55,51;,
 4;55,56,52,51;,
 3;57,56,55;,
 3;56,57,58;,
 4;59,60,61,57;,
 3;58,57,61;,
 3;62,58,61;,
 4;61,63,64,62;,
 4;65,66,67,63;,
 3;63,67,64;,
 3;5,64,67;,
 3;5,67,3;,
 4;68,69,70,71;,
 4;70,69,72,73;,
 4;70,73,74,75;,
 4;76,75,77,78;,
 3;74,77,75;,
 3;77,74,79;,
 4;80,79,81,82;,
 3;74,83,79;,
 4;79,83,84,85;,
 3;84,86,85;,
 4;87,86,88,89;,
 3;84,88,86;,
 3;88,84,90;,
 4;88,90,91,92;,
 4;93,92,94,95;,
 3;91,94,92;,
 3;96,94,91;,
 3;96,97,94;,
 4;98,97,99,100;,
 3;97,96,99;,
 3;101,99,96;,
 4;99,101,102,103;,
 4;104,103,105,106;,
 3;103,102,105;,
 3;107,105,102;,
 4;105,107,108,109;,
 4;110,109,111,112;,
 3;108,111,109;,
 3;113,111,108;,
 4;111,113,114,115;,
 4;116,115,117,118;,
 3;114,117,115;,
 4;117,114,119,120;,
 4;121,120,122,123;,
 4;122,120,119,124;,
 3;125,122,124;,
 3;124,126,125;,
 4;127,125,128,129;,
 3;126,128,125;,
 3;130,128,126;,
 4;128,130,131,132;,
 4;133,132,134,135;,
 3;132,131,134;,
 3;72,134,131;,
 3;72,69,134;,
 4;0,68,71,1;,
 4;76,78,9,8;,
 4;80,82,13,12;,
 4;87,89,20,19;,
 4;93,95,26,25;,
 4;98,100,31,30;,
 4;104,106,37,36;,
 4;110,112,43,42;,
 4;116,118,49,48;,
 4;53,121,123,54;,
 4;59,127,129,60;,
 4;65,133,135,66;,
 4;70,75,6,2;,
 4;1,71,70,2;,
 4;76,8,6,75;,
 4;77,79,11,10;,
 4;9,78,77,10;,
 4;85,86,18,16;,
 4;13,82,85,16;,
 4;86,87,19,18;,
 4;21,88,92,23;,
 4;20,89,88,21;,
 4;23,92,93,25;,
 4;94,97,29,27;,
 4;26,95,94,27;,
 4;97,98,30,29;,
 4;103,104,36,34;,
 4;31,100,99,32;,
 4;99,103,34,32;,
 4;37,106,105,38;,
 4;105,109,40,38;,
 4;109,110,42,40;,
 4;44,43,112,111;,
 4;50,49,118,117;,
 4;51,50,117,120;,
 4;121,53,51,120;,
 4;115,46,44,111;,
 4;116,48,46,115;,
 4;55,54,123,122;,
 4;57,55,122,125;,
 4;59,57,125,127;,
 4;61,60,129,128;,
 4;63,61,128,132;,
 4;133,65,63,132;,
 4;67,134,69,3;,
 4;66,135,134,67;,
 4;68,0,3,69;,
 4;80,12,11,79;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;145,148,149,146;,
 4;148,150,151,149;,
 4;151,150,152,153;,
 4;154,153,152,155;,
 4;142,154,155,141;,
 4;147,136,137,144;,
 4;139,156,157,138;,
 4;157,156,143,140;,
 4;33,35,102,101;,
 4;39,107,102,35;,
 4;108,107,39,41;,
 4;108,41,45,113;,
 4;28,33,101,96;,
 4;28,96,91,24;,
 4;90,22,24,91;,
 4;84,17,22,90;,
 4;114,113,45,47;,
 4;114,47,52,119;,
 4;119,52,56,124;,
 4;126,124,56,58;,
 4;130,126,58,62;,
 4;62,64,131,130;,
 4;15,17,84,83;,
 4;74,7,15,83;,
 4;73,4,7,74;,
 4;72,5,4,73;,
 4;131,64,5,72;,
 4;158,159,139,138;,
 4;160,158,138,137;,
 4;161,160,137,136;,
 4;159,161,136,139;,
 4;159,158,160,161;,
 4;162,161,136,147;,
 4;163,162,147,144;,
 4;160,163,144,137;,
 4;161,160,137,136;,
 4;161,162,163,160;,
 4;164,162,147,146;,
 4;165,164,146,145;,
 4;163,165,145,144;,
 4;162,163,144,147;,
 4;162,164,165,163;,
 4;164,165,145,146;,
 4;166,164,146,149;,
 4;167,166,149,148;,
 4;165,167,148,145;,
 4;165,164,166,167;,
 4;166,167,148,149;,
 4;168,166,149,151;,
 4;169,168,151,150;,
 4;167,169,150,148;,
 4;167,166,168,169;,
 4;168,169,150,151;,
 4;170,168,151,153;,
 4;171,170,153,152;,
 4;169,171,152,150;,
 4;169,168,170,171;,
 4;171,172,155,152;,
 4;170,171,152,153;,
 4;173,170,153,154;,
 4;172,173,154,155;,
 4;172,171,170,173;,
 4;172,174,141,155;,
 4;173,172,155,154;,
 4;175,173,154,142;,
 4;174,175,142,141;,
 4;174,172,173,175;,
 4;158,159,139,138;,
 4;176,158,138,157;,
 4;177,176,157,156;,
 4;159,177,156,139;,
 4;159,158,176,177;,
 4;177,178,143,156;,
 4;176,177,156,157;,
 4;179,176,157,140;,
 4;178,179,140,143;,
 4;178,177,176,179;,
 4;175,178,143,142;,
 4;174,175,142,141;,
 4;179,174,141,140;,
 4;178,179,140,143;,
 4;178,175,174,179;,
 4;160,158,138,137;,
 4;160,163,162,161;,
 4;163,165,164,162;,
 4;165,167,166,164;,
 4;167,169,168,166;,
 4;168,169,171,170;,
 4;171,172,173,170;,
 4;172,174,175,173;,
 4;175,174,179,178;,
 4;159,177,176,158;,
 4;177,178,179,176;,
 4;160,137,144,163;,
 4;163,144,145,165;,
 4;148,167,165,145;,
 4;150,169,167,148;,
 4;169,150,152,171;,
 4;172,171,152,155;,
 4;172,155,141,174;,
 4;141,140,179,174;,
 4;179,140,157,176;,
 4;157,138,158,176;,
 4;162,147,136,161;,
 4;164,146,147,162;,
 4;166,149,146,164;,
 4;166,168,151,149;,
 4;168,170,153,151;,
 4;170,173,154,153;,
 4;154,173,175,142;,
 4;177,156,143,178;,
 4;177,159,139,156;,
 4;155,154,142,141;,
 4;155,152,153,154;,
 4;153,152,150,151;,
 4;151,150,148,149;,
 4;146,149,148,145;,
 4;146,145,144,147;,
 4;136,147,144,137;,
 4;138,157,156,139;,
 4;157,140,143,156;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;192,185,196,197;,
 4;198,199,186,195;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;212,205,216,217;,
 4;218,219,206,215;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;232,225,236,237;,
 4;238,239,226,235;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;252,245,256,257;,
 4;258,259,246,255;;
 
 MeshMaterialList {
  2;
  286;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.310400;0.310400;0.310400;1.000000;;
   6.000000;
   0.700000;0.700000;0.700000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  171;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.034376;0.000000;-0.999409;,
  0.462525;0.000000;0.886606;,
  0.908940;0.000251;0.416928;,
  0.965099;0.000291;-0.261884;,
  0.686284;0.000036;-0.727334;,
  0.209819;0.000000;-0.977740;,
  -0.365084;0.000000;-0.930975;,
  0.864255;0.000000;0.503055;,
  0.999358;0.000000;0.035817;,
  -0.928898;0.000000;0.370336;,
  0.505098;0.000000;-0.863062;,
  0.999226;0.000000;0.039330;,
  -0.867109;0.000000;-0.498118;,
  0.000016;-1.000000;0.000007;,
  -0.899402;0.000000;0.437122;,
  0.000075;-1.000000;0.000008;,
  -0.407199;0.000000;0.913339;,
  0.000100;-1.000000;-0.000015;,
  0.226939;0.001134;0.973908;,
  0.000041;-1.000000;-0.000015;,
  0.716968;0.000000;0.697107;,
  0.980733;0.000000;0.195355;,
  0.379777;0.000000;0.925078;,
  0.000000;-0.000000;1.000000;,
  0.581245;0.000000;0.813729;,
  0.795449;0.000000;0.606021;,
  0.999233;0.000000;0.039155;,
  0.841186;0.000000;-0.540745;,
  0.459437;0.000000;-0.888210;,
  -0.052557;0.000000;-0.998618;,
  -0.591369;0.000000;-0.806401;,
  -0.807387;0.000000;-0.590022;,
  -1.000000;0.000000;0.000000;,
  -0.862692;0.000000;0.505730;,
  -0.424449;0.000000;0.905452;,
  0.323716;0.000000;0.946154;,
  0.998372;0.000000;0.057046;,
  -0.823926;0.000000;0.566697;,
  0.765046;0.000000;0.643976;,
  0.841189;0.000000;-0.540741;,
  0.983200;0.000000;0.182532;,
  0.564290;0.000000;-0.825577;,
  0.076681;0.000000;0.997056;,
  0.968814;0.000000;-0.247788;,
  0.000000;0.000000;-1.000000;,
  0.630326;0.000000;0.776331;,
  0.636820;0.000000;-0.771012;,
  -0.597010;0.000000;-0.802234;,
  0.889823;0.000000;0.456306;,
  0.989788;0.000000;-0.142546;,
  -0.842713;0.000000;-0.538363;,
  0.305407;0.000000;-0.952222;,
  -0.999742;0.000000;-0.022721;,
  -0.302786;0.000000;-0.953059;,
  0.841645;0.000000;-0.540031;,
  -0.823208;0.000000;0.567740;,
  -0.507030;0.000000;0.861928;,
  -0.966163;0.000000;-0.257932;,
  -0.094263;0.000000;-0.995547;,
  -0.725936;0.000000;-0.687763;,
  0.545449;0.000000;-0.838144;,
  0.026305;0.000000;0.999654;,
  -0.989462;0.000000;0.144796;,
  -0.595233;0.000000;-0.803553;,
  0.522572;0.000000;0.852595;,
  -0.657973;0.000000;0.753041;,
  -0.881717;0.000000;-0.471778;,
  -0.274714;0.000000;0.961526;,
  0.900544;0.000000;0.434765;,
  -0.999568;0.000000;-0.029397;,
  -0.599995;0.000000;0.800004;,
  -0.570279;0.000000;-0.821451;,
  0.158839;0.000000;0.987305;,
  -0.738412;0.000000;0.674350;,
  -0.999826;0.000000;0.018657;,
  -0.434218;0.000000;0.900808;,
  -0.115047;0.000000;0.993360;,
  0.192455;0.000000;0.981306;,
  0.484866;0.000000;0.874589;,
  0.687917;0.000000;0.725789;,
  -0.679339;0.000000;0.733824;,
  -0.897055;0.000000;0.441919;,
  -0.997967;0.000000;0.063733;,
  -0.929775;0.000000;-0.368129;,
  0.870645;0.000000;0.491913;,
  0.990132;0.000000;0.140134;,
  0.994556;0.000000;-0.104200;,
  0.899243;0.000000;-0.437450;,
  0.718465;0.000000;-0.695564;,
  0.503384;0.000000;-0.864063;,
  -0.749792;0.000000;-0.661674;,
  -0.516497;0.000000;-0.856289;,
  -0.177762;0.000000;-0.984073;,
  0.153948;0.000000;-0.988079;,
  -0.527106;0.000000;0.849800;,
  -0.005135;0.000000;0.999987;,
  -0.000016;1.000000;-0.000007;,
  -0.237591;0.000000;-0.971365;,
  -0.506024;0.000000;-0.862520;,
  -0.000082;1.000000;0.000073;,
  0.899402;0.000000;-0.437122;,
  -0.916150;-0.000247;-0.400836;,
  0.407199;0.000000;-0.913339;,
  -0.000151;1.000000;0.000007;,
  -0.960456;-0.000281;0.278433;,
  -0.226939;-0.001134;-0.973908;,
  -0.000085;1.000000;-0.000074;,
  -0.661174;-0.000030;0.750233;,
  -0.716968;0.000000;-0.697107;,
  -0.203455;0.000000;0.979084;,
  -0.980733;0.000000;-0.195355;,
  0.927744;0.000000;-0.373218;,
  0.348162;0.000000;0.937434;,
  -0.927744;0.000000;0.373218;,
  0.451737;0.000000;-0.892151;,
  0.570721;0.000000;0.821144;,
  0.757991;0.000000;-0.652265;,
  0.925483;0.000000;-0.378789;,
  -0.379777;0.000000;-0.925078;,
  -0.035738;0.000000;0.999361;,
  0.997796;0.000000;-0.066357;,
  -0.992817;0.000000;-0.119644;,
  -0.897180;0.000000;-0.441665;,
  0.506024;0.000000;0.862520;,
  0.916150;0.000247;0.400836;,
  0.960456;0.000281;-0.278433;,
  0.661174;0.000030;-0.750233;,
  0.203455;0.000000;-0.979084;,
  -0.348162;0.000000;-0.937434;,
  -0.925483;0.000000;0.378789;,
  0.000016;-1.000000;0.000007;,
  0.000082;-1.000000;-0.000073;,
  0.000151;-1.000000;-0.000007;,
  0.000085;-1.000000;0.000074;,
  -0.000016;1.000000;-0.000007;,
  -0.000075;1.000000;-0.000008;,
  -0.000100;1.000000;0.000015;,
  -0.000041;1.000000;0.000015;,
  0.365084;0.000000;0.930975;,
  -0.209819;0.000000;0.977740;,
  -0.686284;-0.000036;0.727334;,
  -0.965099;-0.000291;0.261884;,
  -0.908940;-0.000251;-0.416928;,
  -0.462525;0.000000;-0.886606;,
  0.928898;0.000000;-0.370336;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;;
  286;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;70,70,70,70;,
  4;71,71,71,71;,
  4;72,72,72,72;,
  4;2,2,12,12;,
  4;10,9,9,10;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,6,7,7;,
  4;8,7,7,8;,
  4;73,8,8,73;,
  4;3,74,74,3;,
  4;75,11,11,75;,
  4;11,11,76,76;,
  4;77,78,78,77;,
  4;79,79,78,78;,
  4;80,79,79,80;,
  4;80,80,81,81;,
  4;82,77,77,82;,
  4;82,82,83,83;,
  4;84,84,83,83;,
  4;85,85,84,84;,
  4;86,81,81,86;,
  4;86,86,87,87;,
  4;87,87,88,88;,
  4;89,88,88,89;,
  4;90,89,89,90;,
  4;90,91,91,90;,
  4;92,85,85,92;,
  4;93,93,92,92;,
  4;94,94,93,93;,
  4;95,95,94,94;,
  4;91,91,95,95;,
  4;14,14,14,14;,
  4;1,1,1,1;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;96,96,97,97;,
  4;15,1,1,15;,
  4;16,16,16,16;,
  4;0,98,98,0;,
  4;13,13,13,13;,
  4;99,100,100,99;,
  4;17,15,15,17;,
  4;18,18,18,18;,
  4;98,101,101,98;,
  4;102,102,102,102;,
  4;100,103,103,100;,
  4;104,104,104,104;,
  4;19,17,17,19;,
  4;20,20,20,20;,
  4;101,105,105,101;,
  4;103,103,106,106;,
  4;107,107,107,107;,
  4;21,19,19,21;,
  4;22,22,22,22;,
  4;105,108,108,105;,
  4;106,106,109,109;,
  4;110,110,110,110;,
  4;1,21,21,1;,
  4;23,23,23,23;,
  4;108,0,0,108;,
  4;109,109,111,111;,
  4;0,0,0,0;,
  4;112,112,112,112;,
  4;1,1,1,1;,
  4;113,113,113,113;,
  4;114,111,111,114;,
  4;0,0,0,0;,
  4;115,115,115,115;,
  4;1,1,1,1;,
  4;116,116,116,116;,
  4;117,114,114,117;,
  4;14,14,14,14;,
  4;0,0,0,0;,
  4;24,24,24,24;,
  4;1,1,1,1;,
  4;118,118,119,119;,
  4;1,1,1,1;,
  4;120,120,120,120;,
  4;0,0,0,0;,
  4;121,121,121,121;,
  4;122,119,119,122;,
  4;0,0,0,0;,
  4;116,116,116,116;,
  4;1,1,1,1;,
  4;121,121,121,121;,
  4;123,124,124,123;,
  4;1,1,1,1;,
  4;97,125,125,97;,
  4;125,126,126,125;,
  4;126,127,127,126;,
  4;127,128,128,127;,
  4;128,128,129,129;,
  4;129,130,130,129;,
  4;130,124,124,130;,
  4;124,124,123,123;,
  4;96,131,131,96;,
  4;131,123,123,131;,
  4;1,1,132,132;,
  4;132,132,133,133;,
  4;134,134,133,133;,
  4;135,135,134,134;,
  4;135,135,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;136,136,0,0;,
  4;137,137,136,136;,
  4;138,138,137,137;,
  4;138,139,139,138;,
  4;139,0,0,139;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;140,140,9,9;,
  4;140,141,141,140;,
  4;141,141,142,142;,
  4;142,142,143,143;,
  4;144,143,143,144;,
  4;144,144,145,145;,
  4;2,145,145,2;,
  4;12,146,146,12;,
  4;146,10,10,146;,
  4;147,147,147,147;,
  4;148,148,148,148;,
  4;149,149,149,149;,
  4;150,150,150,150;,
  4;151,151,151,151;,
  4;152,152,152,152;,
  4;153,153,153,153;,
  4;154,154,154,154;,
  4;155,155,155,155;,
  4;156,156,156,156;,
  4;157,157,157,157;,
  4;158,158,158,158;,
  4;159,159,159,159;,
  4;160,160,160,160;,
  4;161,161,161,161;,
  4;162,162,162,162;,
  4;163,163,163,163;,
  4;164,164,164,164;,
  4;165,165,165,165;,
  4;166,166,166,166;,
  4;167,167,167,167;,
  4;168,168,168,168;,
  4;169,169,169,169;,
  4;170,170,170,170;;
 }
 MeshTextureCoords {
  260;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
