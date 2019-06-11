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
 185;
 -6.81987;21.41606;4.41090;,
 6.81987;21.41606;4.41090;,
 6.81987;21.41606;-4.20951;,
 -6.81987;21.41606;-4.20951;,
 -6.81987;19.29270;-4.51416;,
 6.81987;19.29270;-4.51416;,
 6.81987;2.30588;-4.51416;,
 -6.81987;2.30588;-4.51416;,
 -6.81987;0.18252;-4.20951;,
 6.81987;0.18252;-4.20951;,
 6.81987;0.18252;4.41090;,
 -6.81987;0.18252;4.41090;,
 -6.81987;2.30588;5.48845;,
 6.81987;2.30588;5.48845;,
 6.81987;19.29270;5.48845;,
 -6.81987;19.29270;5.48845;,
 8.52483;19.29270;4.41090;,
 8.52483;2.30588;4.41090;,
 8.52483;2.30588;-4.20951;,
 8.52483;19.29270;-4.20951;,
 -8.52483;2.30588;4.41090;,
 -8.52483;19.29270;4.41090;,
 -8.52483;19.29270;-4.20951;,
 -8.52483;2.30588;-4.20951;,
 -6.81987;21.41606;-4.20951;,
 6.81987;21.41606;-4.20951;,
 6.81987;21.25442;-4.62187;,
 -6.81987;21.25442;-4.62187;,
 6.81987;20.79414;-4.97146;,
 -6.81987;20.79414;-4.97146;,
 6.81987;20.10528;-5.20504;,
 -6.81987;20.10528;-5.20504;,
 6.81987;19.29270;-4.51416;,
 -6.81987;0.34415;-4.62187;,
 6.81987;0.34415;-4.62187;,
 6.81987;0.18252;-4.20951;,
 -6.81987;0.80444;-4.97146;,
 6.81987;0.80444;-4.97146;,
 -6.81987;1.49330;-5.20504;,
 6.81987;1.49330;-5.20504;,
 -6.81987;2.30588;-4.51416;,
 6.81987;2.30588;-4.51416;,
 -6.81987;21.25442;4.82326;,
 6.81987;21.25442;4.82326;,
 6.81987;21.41606;4.41090;,
 -6.81987;20.79414;5.17284;,
 6.81987;20.79414;5.17284;,
 -6.81987;20.10528;5.40642;,
 6.81987;20.10528;5.40642;,
 -6.81987;19.29270;5.48845;,
 6.81987;19.29270;5.48845;,
 -6.81987;0.18252;4.41090;,
 6.81987;0.18252;4.41090;,
 6.81987;0.34415;4.82326;,
 -6.81987;0.34415;4.82326;,
 6.81987;0.80444;5.17284;,
 -6.81987;0.80444;5.17284;,
 6.81987;1.49330;5.40642;,
 -6.81987;1.49330;5.40642;,
 6.81987;2.30588;5.48845;,
 7.47233;21.25442;4.41090;,
 7.47233;21.25442;-4.20951;,
 8.02546;20.79414;4.41090;,
 8.02546;20.79414;-4.20951;,
 8.39505;20.10528;4.41090;,
 8.39505;20.10528;-4.20951;,
 8.52483;19.29270;-4.20951;,
 7.47233;0.34415;-4.20951;,
 7.47233;0.34415;4.41090;,
 8.02546;0.80444;-4.20951;,
 8.02546;0.80444;4.41090;,
 8.39505;1.49330;-4.20951;,
 8.39505;1.49330;4.41090;,
 8.52483;2.30588;-4.20951;,
 8.52483;2.30588;4.41090;,
 -7.47233;21.25442;-4.20951;,
 -7.47233;21.25442;4.41090;,
 -8.02546;20.79414;-4.20951;,
 -8.02546;20.79414;4.41090;,
 -8.39505;20.10528;-4.20951;,
 -8.39505;20.10528;4.41090;,
 -8.52483;19.29270;-4.20951;,
 -8.52483;19.29270;4.41090;,
 -7.47233;0.34415;4.41090;,
 -7.47233;0.34415;-4.20951;,
 -8.02546;0.80444;4.41090;,
 -8.02546;0.80444;-4.20951;,
 -8.39505;1.49330;4.41090;,
 -8.39505;1.49330;-4.20951;,
 -8.52483;2.30588;-4.20951;,
 7.47233;19.29270;-5.20504;,
 7.47233;2.30588;-5.20504;,
 8.02546;19.29270;-4.97146;,
 8.02546;2.30588;-4.97146;,
 8.39505;19.29270;-4.62187;,
 8.39505;2.30588;-4.62187;,
 7.47233;2.30588;5.40642;,
 7.47233;19.29270;5.40642;,
 8.02546;2.30588;5.17284;,
 8.02546;19.29270;5.17284;,
 8.39505;2.30588;4.82326;,
 8.39505;19.29270;4.82326;,
 -7.47233;2.30588;-5.20504;,
 -7.47233;19.29270;-5.20504;,
 -8.02546;2.30588;-4.97146;,
 -8.02546;19.29270;-4.97146;,
 -8.39505;2.30588;-4.62187;,
 -8.39505;19.29270;-4.62187;,
 -7.47233;19.29270;5.40642;,
 -7.47233;2.30588;5.40642;,
 -8.02546;19.29270;5.17284;,
 -8.02546;2.30588;5.17284;,
 -8.39505;19.29270;4.82326;,
 -8.39505;2.30588;4.82326;,
 7.67235;20.79414;-4.74829;,
 8.18402;20.10528;-4.70728;,
 7.60746;20.10528;-5.07167;,
 -7.67235;20.79414;-4.74829;,
 -8.18402;20.10528;-4.70728;,
 -7.60746;20.10528;-5.07167;,
 7.67235;0.80444;-4.74829;,
 8.18402;1.49330;-4.70728;,
 7.60746;1.49330;-5.07167;,
 7.67235;20.79414;4.94967;,
 8.18402;20.10528;4.90866;,
 7.60746;20.10528;5.27305;,
 -7.67235;0.80444;-4.74829;,
 -8.18402;1.49330;-4.70728;,
 -7.60746;1.49330;-5.07167;,
 7.67235;0.80444;4.94967;,
 8.18402;1.49330;4.90866;,
 7.60746;1.49330;5.27305;,
 -7.67235;20.79414;4.94967;,
 -8.18402;20.10528;4.90866;,
 -7.60746;20.10528;5.27305;,
 -7.67235;0.80444;4.94967;,
 -8.18402;1.49330;4.90866;,
 -7.60746;1.49330;5.27305;,
 -6.81987;20.79414;-4.97146;,
 6.81987;20.79414;-4.97146;,
 -0.37414;2.53975;-4.97146;,
 -0.61524;18.68251;-5.54639;,
 -0.87495;19.68162;-5.45018;,
 0.14282;19.67462;-5.45086;,
 -0.09583;18.66155;-5.54840;,
 1.11819;12.32289;-6.15875;,
 -1.79276;12.37655;-6.15358;,
 -0.37323;9.60420;-6.42053;,
 -21.43220;51.28556;6.82397;,
 -21.14174;51.47058;6.95616;,
 14.60749;-4.64441;6.95616;,
 14.31704;-4.82948;6.82397;,
 -21.01519;51.55120;7.29316;,
 14.73404;-4.56380;7.29316;,
 -21.12668;51.48014;7.63756;,
 14.62254;-4.63482;7.63756;,
 -21.41090;51.29902;7.78761;,
 14.33831;-4.81591;7.78761;,
 -21.70137;51.11405;7.65540;,
 14.04786;-5.00095;7.65540;,
 -21.82792;51.03344;7.31840;,
 13.92132;-5.08155;7.31840;,
 -21.71642;51.10446;6.97401;,
 14.03282;-5.01054;6.97401;,
 -21.43220;51.28556;6.82397;,
 14.31704;-4.82948;6.82397;,
 -21.42154;51.29229;7.30578;,
 -21.42154;51.29229;7.30578;,
 -21.42154;51.29229;7.30578;,
 -21.42154;51.29229;7.30578;,
 -21.42154;51.29229;7.30578;,
 -21.42154;51.29229;7.30578;,
 -21.42154;51.29229;7.30578;,
 -21.42154;51.29229;7.30578;,
 14.32767;-4.82268;7.30578;,
 14.32767;-4.82268;7.30578;,
 14.32767;-4.82268;7.30578;,
 14.32767;-4.82268;7.30578;,
 14.32767;-4.82268;7.30578;,
 14.32767;-4.82268;7.30578;,
 14.32767;-4.82268;7.30578;,
 14.32767;-4.82268;7.30578;,
 -13.18564;39.34031;7.47311;,
 -8.76302;59.30548;7.09454;,
 -20.95618;51.53759;7.47311;;
 
 212;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;31,30,32,4;,
 4;33,34,35,8;,
 4;36,37,34,33;,
 4;38,39,37,36;,
 4;40,41,39,38;,
 4;42,43,44,0;,
 4;45,46,43,42;,
 4;47,48,46,45;,
 4;49,50,48,47;,
 4;51,52,53,54;,
 4;54,53,55,56;,
 4;56,55,57,58;,
 4;58,57,59,12;,
 4;25,44,60,61;,
 4;61,60,62,63;,
 4;63,62,64,65;,
 4;65,64,16,66;,
 4;52,35,67,68;,
 4;68,67,69,70;,
 4;70,69,71,72;,
 4;72,71,73,74;,
 4;0,24,75,76;,
 4;76,75,77,78;,
 4;78,77,79,80;,
 4;80,79,81,82;,
 4;8,51,83,84;,
 4;84,83,85,86;,
 4;86,85,87,88;,
 4;88,87,20,89;,
 4;41,32,90,91;,
 4;91,90,92,93;,
 4;93,92,94,95;,
 4;95,94,66,73;,
 4;50,59,96,97;,
 4;97,96,98,99;,
 4;99,98,100,101;,
 4;101,100,74,16;,
 4;4,40,102,103;,
 4;103,102,104,105;,
 4;105,104,106,107;,
 4;107,106,89,81;,
 4;12,49,108,109;,
 4;109,108,110,111;,
 4;111,110,112,113;,
 4;113,112,82,20;,
 3;25,61,26;,
 3;61,63,114;,
 3;114,26,61;,
 3;26,114,28;,
 3;63,65,115;,
 3;115,114,63;,
 3;114,115,116;,
 3;116,28,114;,
 3;28,116,30;,
 3;65,66,94;,
 3;94,115,65;,
 3;115,94,92;,
 3;92,116,115;,
 3;116,92,90;,
 3;90,30,116;,
 3;30,90,32;,
 3;27,75,24;,
 3;117,77,75;,
 3;75,27,117;,
 3;29,117,27;,
 3;118,79,77;,
 3;77,117,118;,
 3;119,118,117;,
 3;117,29,119;,
 3;31,119,29;,
 3;107,81,79;,
 3;79,118,107;,
 3;105,107,118;,
 3;118,119,105;,
 3;103,105,119;,
 3;119,31,103;,
 3;4,103,31;,
 3;34,67,35;,
 3;120,69,67;,
 3;67,34,120;,
 3;37,120,34;,
 3;121,71,69;,
 3;69,120,121;,
 3;122,121,120;,
 3;120,37,122;,
 3;39,122,37;,
 3;95,73,71;,
 3;71,121,95;,
 3;93,95,121;,
 3;121,122,93;,
 3;91,93,122;,
 3;122,39,91;,
 3;41,91,39;,
 3;43,60,44;,
 3;123,62,60;,
 3;60,43,123;,
 3;46,123,43;,
 3;124,64,62;,
 3;62,123,124;,
 3;125,124,123;,
 3;123,46,125;,
 3;48,125,46;,
 3;101,16,64;,
 3;64,124,101;,
 3;99,101,124;,
 3;124,125,99;,
 3;97,99,125;,
 3;125,48,97;,
 3;50,97,48;,
 3;8,84,33;,
 3;84,86,126;,
 3;126,33,84;,
 3;33,126,36;,
 3;86,88,127;,
 3;127,126,86;,
 3;126,127,128;,
 3;128,36,126;,
 3;36,128,38;,
 3;88,89,106;,
 3;106,127,88;,
 3;127,106,104;,
 3;104,128,127;,
 3;128,104,102;,
 3;102,38,128;,
 3;38,102,40;,
 3;52,68,53;,
 3;68,70,129;,
 3;129,53,68;,
 3;53,129,55;,
 3;70,72,130;,
 3;130,129,70;,
 3;129,130,131;,
 3;131,55,129;,
 3;55,131,57;,
 3;72,74,100;,
 3;100,130,72;,
 3;130,100,98;,
 3;98,131,130;,
 3;131,98,96;,
 3;96,57,131;,
 3;57,96,59;,
 3;0,76,42;,
 3;76,78,132;,
 3;132,42,76;,
 3;42,132,45;,
 3;78,80,133;,
 3;133,132,78;,
 3;132,133,134;,
 3;134,45,132;,
 3;45,134,47;,
 3;80,82,112;,
 3;112,133,80;,
 3;133,112,110;,
 3;110,134,133;,
 3;134,110,108;,
 3;108,47,134;,
 3;47,108,49;,
 3;54,83,51;,
 3;135,85,83;,
 3;83,54,135;,
 3;56,135,54;,
 3;136,87,85;,
 3;85,135,136;,
 3;137,136,135;,
 3;135,56,137;,
 3;58,137,56;,
 3;113,20,87;,
 3;87,136,113;,
 3;111,113,136;,
 3;136,137,111;,
 3;109,111,137;,
 3;137,58,109;,
 3;12,109,58;,
 3;138,139,140;,
 4;141,142,143,144;,
 4;141,144,145,146;,
 3;146,145,147;,
 4;148,149,150,151;,
 4;149,152,153,150;,
 4;152,154,155,153;,
 4;154,156,157,155;,
 4;156,158,159,157;,
 4;158,160,161,159;,
 4;160,162,163,161;,
 4;162,164,165,163;,
 3;166,149,148;,
 3;167,152,149;,
 3;168,154,152;,
 3;169,156,154;,
 3;170,158,156;,
 3;171,160,158;,
 3;172,162,160;,
 3;173,164,162;,
 3;174,151,150;,
 3;175,150,153;,
 3;176,153,155;,
 3;177,155,157;,
 3;178,157,159;,
 3;179,159,161;,
 3;180,161,163;,
 3;181,163,165;,
 3;182,183,184;,
 3;184,183,182;;
 
 MeshMaterialList {
  8;
  212;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  5,
  0,
  0,
  0,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  6,
  6;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.664800;0.501600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.078400;0.084800;0.310400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.009600;0.081600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.062400;0.109600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game134\\Desktop\\nekutai.jpg";
   }
  }
  Material {
   0.034400;0.024800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  157;
  -0.119157;0.975572;0.184558;,
  0.119157;0.975572;0.184558;,
  -0.119157;0.975572;-0.184558;,
  0.119157;0.975572;-0.184558;,
  0.384569;-0.326949;-0.863256;,
  -0.384569;-0.326949;-0.863256;,
  0.384569;0.326949;-0.863256;,
  -0.384569;0.326949;-0.863256;,
  -0.119150;-0.975574;-0.184548;,
  0.119150;-0.975574;-0.184548;,
  -0.119150;-0.975574;0.184548;,
  0.119150;-0.975574;0.184548;,
  -0.062416;-0.050186;0.996788;,
  0.062416;-0.050186;0.996788;,
  -0.062416;0.050186;0.996788;,
  0.062416;0.050186;0.996788;,
  0.985367;0.078214;0.151442;,
  0.985367;-0.078214;0.151442;,
  0.985367;0.078214;-0.151442;,
  0.985367;-0.078214;-0.151442;,
  -0.985367;-0.078214;0.151442;,
  -0.985367;0.078214;0.151442;,
  -0.985367;-0.078214;-0.151442;,
  -0.985367;0.078214;-0.151442;,
  -0.159575;0.792219;-0.589004;,
  0.159575;0.792219;-0.589004;,
  -0.120909;0.453181;-0.883181;,
  0.120909;0.453181;-0.883181;,
  0.071671;-0.089772;-0.993380;,
  -0.071671;-0.089772;-0.993380;,
  -0.159575;-0.792220;-0.589002;,
  0.159575;-0.792220;-0.589002;,
  -0.120909;-0.453177;-0.883183;,
  0.120909;-0.453177;-0.883183;,
  0.071671;0.089772;-0.993380;,
  -0.071671;0.089772;-0.993380;,
  -0.159577;0.792214;0.589009;,
  0.159577;0.792214;0.589009;,
  -0.120909;0.453176;0.883183;,
  0.120909;0.453176;0.883183;,
  -0.090344;0.195869;0.976460;,
  0.090344;0.195869;0.976460;,
  -0.159576;-0.792216;0.589008;,
  0.159576;-0.792216;0.589008;,
  -0.120909;-0.453172;0.883185;,
  0.120909;-0.453172;0.883185;,
  -0.090344;-0.195869;0.976459;,
  0.090344;-0.195869;0.976459;,
  0.425642;0.864455;0.267481;,
  0.425642;0.864456;-0.267479;,
  0.758455;0.601560;0.250743;,
  0.758456;0.601561;-0.250739;,
  0.932907;0.291421;0.211564;,
  0.932907;0.291421;-0.211561;,
  0.425642;-0.864455;0.267480;,
  0.425642;-0.864456;-0.267478;,
  0.758457;-0.601557;0.250744;,
  0.758458;-0.601558;-0.250740;,
  0.932906;-0.291421;0.211564;,
  0.932907;-0.291421;-0.211561;,
  -0.425642;0.864455;0.267481;,
  -0.425642;0.864456;-0.267479;,
  -0.758455;0.601560;0.250743;,
  -0.758456;0.601561;-0.250739;,
  -0.932907;0.291421;0.211564;,
  -0.932907;0.291421;-0.211561;,
  -0.425642;-0.864455;0.267480;,
  -0.425642;-0.864456;-0.267478;,
  -0.758457;-0.601557;0.250744;,
  -0.758458;-0.601558;-0.250740;,
  -0.932906;-0.291421;0.211564;,
  -0.932907;-0.291421;-0.211561;,
  -0.461391;0.144023;-0.875429;,
  -0.461391;-0.144023;-0.875429;,
  0.542856;-0.072253;-0.836712;,
  0.542856;0.072253;-0.836712;,
  0.860454;-0.092111;-0.501133;,
  0.860454;0.092112;-0.501133;,
  0.240516;-0.064367;0.968509;,
  0.240516;0.064368;0.968509;,
  0.542851;-0.072254;0.836715;,
  0.542851;0.072254;0.836715;,
  0.860450;-0.092113;0.501139;,
  0.860450;0.092113;0.501139;,
  0.461391;0.144023;-0.875429;,
  0.461391;-0.144023;-0.875429;,
  -0.542856;-0.072253;-0.836712;,
  -0.542856;0.072253;-0.836712;,
  -0.860454;-0.092111;-0.501133;,
  -0.860454;0.092112;-0.501133;,
  -0.240516;-0.064367;0.968509;,
  -0.240516;0.064368;0.968509;,
  -0.542851;-0.072254;0.836715;,
  -0.542851;0.072254;0.836715;,
  -0.860450;-0.092113;0.501139;,
  -0.860450;0.092113;0.501139;,
  0.454124;0.579306;-0.676887;,
  0.724398;0.302942;-0.619253;,
  0.335992;0.242693;-0.910060;,
  -0.454124;0.579306;-0.676887;,
  -0.724398;0.302942;-0.619253;,
  -0.335992;0.242693;-0.910060;,
  0.454126;-0.579302;-0.676889;,
  0.724398;-0.302943;-0.619253;,
  0.335992;-0.242693;-0.910060;,
  0.454124;0.579302;0.676890;,
  0.724394;0.302943;0.619257;,
  0.335992;0.242693;0.910060;,
  -0.454126;-0.579302;-0.676889;,
  -0.724398;-0.302943;-0.619253;,
  -0.335992;-0.242693;-0.910060;,
  0.454125;-0.579298;0.676893;,
  0.724394;-0.302943;0.619257;,
  0.335992;-0.242694;0.910060;,
  -0.454124;0.579302;0.676890;,
  -0.724394;0.302943;0.619257;,
  -0.335992;0.242693;0.910060;,
  -0.454125;-0.579298;0.676893;,
  -0.724394;-0.302943;0.619257;,
  -0.335992;-0.242694;0.910060;,
  0.000000;0.000000;-1.000000;,
  0.000006;0.095846;-0.995396;,
  0.000005;0.095848;-0.995396;,
  0.000003;0.095845;-0.995396;,
  -0.000001;0.095846;-0.995396;,
  0.388661;-0.043134;-0.920371;,
  0.388661;0.043134;-0.920371;,
  -0.388661;0.043134;-0.920371;,
  -0.388661;-0.043134;-0.920371;,
  -0.537290;0.843398;0.000055;,
  -0.022083;-0.014068;-0.999657;,
  0.580549;0.369851;-0.725378;,
  0.843102;0.537116;-0.026176;,
  0.611769;0.389740;0.688362;,
  0.022062;0.014055;0.999658;,
  -0.580565;-0.369861;0.725360;,
  -0.843102;-0.537116;0.026170;,
  -0.611778;-0.389746;-0.688350;,
  0.537312;-0.843384;0.000014;,
  0.022077;0.014065;0.999657;,
  -0.537318;0.843379;0.000079;,
  -0.537307;0.843387;0.000119;,
  -0.537354;0.843357;0.000046;,
  -0.537362;0.843352;0.000062;,
  -0.537262;0.843415;0.000069;,
  -0.537196;0.843458;0.000020;,
  -0.537236;0.843432;-0.000012;,
  -0.537283;0.843402;0.000061;,
  0.537326;-0.843375;0.000039;,
  0.537324;-0.843376;0.000010;,
  0.537300;-0.843391;0.000010;,
  0.537316;-0.843381;0.000018;,
  0.537325;-0.843375;-0.000002;,
  0.537307;-0.843387;-0.000014;,
  0.537296;-0.843394;0.000010;,
  0.537299;-0.843392;0.000043;,
  -0.022077;-0.014065;-0.999657;;
  212;
  4;0,1,3,2;,
  4;4,5,7,6;,
  4;8,9,11,10;,
  4;12,13,15,14;,
  4;16,17,19,18;,
  4;20,21,23,22;,
  4;2,3,25,24;,
  4;24,25,27,26;,
  4;26,27,29,28;,
  4;28,29,5,4;,
  4;30,31,9,8;,
  4;32,33,31,30;,
  4;34,35,33,32;,
  4;6,7,35,34;,
  4;36,37,1,0;,
  4;38,39,37,36;,
  4;40,41,39,38;,
  4;14,15,41,40;,
  4;10,11,43,42;,
  4;42,43,45,44;,
  4;44,45,47,46;,
  4;46,47,13,12;,
  4;3,1,48,49;,
  4;49,48,50,51;,
  4;51,50,52,53;,
  4;53,52,16,18;,
  4;11,9,55,54;,
  4;54,55,57,56;,
  4;56,57,59,58;,
  4;58,59,19,17;,
  4;0,2,61,60;,
  4;60,61,63,62;,
  4;62,63,65,64;,
  4;64,65,23,21;,
  4;8,10,66,67;,
  4;67,66,68,69;,
  4;69,68,70,71;,
  4;71,70,20,22;,
  4;7,5,73,72;,
  4;125,126,75,74;,
  4;74,75,77,76;,
  4;76,77,18,19;,
  4;15,13,78,79;,
  4;79,78,80,81;,
  4;81,80,82,83;,
  4;83,82,17,16;,
  4;4,6,84,85;,
  4;127,128,86,87;,
  4;87,86,88,89;,
  4;89,88,22,23;,
  4;12,14,91,90;,
  4;90,91,93,92;,
  4;92,93,95,94;,
  4;94,95,21,20;,
  3;3,49,25;,
  3;49,51,96;,
  3;96,25,49;,
  3;25,96,27;,
  3;51,53,97;,
  3;97,96,51;,
  3;96,97,98;,
  3;98,27,96;,
  3;27,98,29;,
  3;53,18,77;,
  3;77,97,53;,
  3;97,77,75;,
  3;75,98,97;,
  3;98,75,126;,
  3;73,29,98;,
  3;29,73,5;,
  3;24,61,2;,
  3;99,63,61;,
  3;61,24,99;,
  3;26,99,24;,
  3;100,65,63;,
  3;63,99,100;,
  3;101,100,99;,
  3;99,26,101;,
  3;28,101,26;,
  3;89,23,65;,
  3;65,100,89;,
  3;87,89,100;,
  3;100,101,87;,
  3;127,87,101;,
  3;101,28,85;,
  3;4,85,28;,
  3;31,55,9;,
  3;102,57,55;,
  3;55,31,102;,
  3;33,102,31;,
  3;103,59,57;,
  3;57,102,103;,
  3;104,103,102;,
  3;102,33,104;,
  3;35,104,33;,
  3;76,19,59;,
  3;59,103,76;,
  3;74,76,103;,
  3;103,104,74;,
  3;125,74,104;,
  3;104,35,72;,
  3;7,72,35;,
  3;37,48,1;,
  3;105,50,48;,
  3;48,37,105;,
  3;39,105,37;,
  3;106,52,50;,
  3;50,105,106;,
  3;107,106,105;,
  3;105,39,107;,
  3;41,107,39;,
  3;83,16,52;,
  3;52,106,83;,
  3;81,83,106;,
  3;106,107,81;,
  3;79,81,107;,
  3;107,41,79;,
  3;15,79,41;,
  3;8,67,30;,
  3;67,69,108;,
  3;108,30,67;,
  3;30,108,32;,
  3;69,71,109;,
  3;109,108,69;,
  3;108,109,110;,
  3;110,32,108;,
  3;32,110,34;,
  3;71,22,88;,
  3;88,109,71;,
  3;109,88,86;,
  3;86,110,109;,
  3;110,86,128;,
  3;84,34,110;,
  3;34,84,6;,
  3;11,54,43;,
  3;54,56,111;,
  3;111,43,54;,
  3;43,111,45;,
  3;56,58,112;,
  3;112,111,56;,
  3;111,112,113;,
  3;113,45,111;,
  3;45,113,47;,
  3;58,17,82;,
  3;82,112,58;,
  3;112,82,80;,
  3;80,113,112;,
  3;113,80,78;,
  3;78,47,113;,
  3;47,78,13;,
  3;0,60,36;,
  3;60,62,114;,
  3;114,36,60;,
  3;36,114,38;,
  3;62,64,115;,
  3;115,114,62;,
  3;114,115,116;,
  3;116,38,114;,
  3;38,116,40;,
  3;64,21,95;,
  3;95,115,64;,
  3;115,95,93;,
  3;93,116,115;,
  3;116,93,91;,
  3;91,40,116;,
  3;40,91,14;,
  3;42,66,10;,
  3;117,68,66;,
  3;66,42,117;,
  3;44,117,42;,
  3;118,70,68;,
  3;68,117,118;,
  3;119,118,117;,
  3;117,44,119;,
  3;46,119,44;,
  3;94,20,70;,
  3;70,118,94;,
  3;92,94,118;,
  3;118,119,92;,
  3;90,92,119;,
  3;119,46,90;,
  3;12,90,46;,
  3;120,120,120;,
  4;121,122,122,121;,
  4;121,121,123,123;,
  3;123,123,124;,
  4;130,131,131,130;,
  4;131,132,132,131;,
  4;132,133,133,132;,
  4;133,134,134,133;,
  4;134,135,135,134;,
  4;135,136,136,135;,
  4;136,137,137,136;,
  4;137,130,130,137;,
  3;129,140,141;,
  3;129,142,140;,
  3;129,143,142;,
  3;129,144,143;,
  3;129,145,144;,
  3;129,146,145;,
  3;129,147,146;,
  3;129,141,147;,
  3;138,148,149;,
  3;138,149,150;,
  3;138,150,151;,
  3;138,151,152;,
  3;138,152,153;,
  3;138,153,154;,
  3;138,154,155;,
  3;138,155,148;,
  3;139,139,139;,
  3;156,156,156;;
 }
 MeshTextureCoords {
  185;
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
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
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
