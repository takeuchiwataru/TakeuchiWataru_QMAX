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
 140;
 -4.73460;8.42360;46.01537;,
 3.94920;8.42360;46.01537;,
 4.44540;8.42360;37.33156;,
 -4.48650;8.42360;37.57967;,
 4.44930;8.42360;29.52976;,
 -4.48290;8.42360;29.77787;,
 13.87140;8.42360;34.10656;,
 13.87500;8.42360;26.30476;,
 21.81300;8.42360;30.13637;,
 29.07030;8.42360;21.51436;,
 22.24740;8.42360;18.41296;,
 33.65640;8.42360;15.23956;,
 26.83350;8.42360;12.13816;,
 35.42820;8.41461;4.91087;,
 45.50760;8.41461;4.91087;,
 45.81780;8.42360;-2.98663;,
 35.73840;8.42360;-2.98663;,
 28.60500;8.42360;-2.21114;,
 33.18210;8.42360;-12.98024;,
 26.04900;8.42360;-12.20503;,
 29.69070;8.42360;-20.50934;,
 18.58770;8.42360;-21.71894;,
 21.31680;8.42360;-27.42524;,
 13.37730;8.42360;-31.89134;,
 11.14440;8.42360;-26.68094;,
 6.14790;8.42360;-34.21004;,
 3.91500;8.42360;-28.99963;,
 4.44540;8.42360;-46.03364;,
 -4.98270;8.42360;-45.53744;,
 -5.23080;8.42360;-34.62044;,
 -6.47160;8.42360;-28.16984;,
 -12.99600;8.42360;-32.15353;,
 -14.23650;8.42360;-25.70263;,
 -21.35820;8.42360;-28.66604;,
 -18.62880;8.42360;-21.96704;,
 -28.77360;8.42360;-20.83874;,
 -26.04450;8.42360;-14.13974;,
 -33.26730;8.42360;-14.77184;,
 -36.27540;8.42360;-3.06913;,
 -29.18100;8.42360;-2.81503;,
 -45.67290;8.42360;-3.06913;,
 -45.67290;8.42360;5.57327;,
 -36.24480;8.42360;5.32517;,
 -29.27850;8.42360;6.07127;,
 -34.75620;8.42360;15.49756;,
 -27.56101;8.42360;13.76086;,
 -29.54580;8.42360;22.94117;,
 -23.09490;8.42360;19.21937;,
 -21.82950;8.42360;29.68306;,
 -15.37860;8.42360;25.96126;,
 -14.90730;8.42360;34.60216;,
 -4.73460;-7.83640;46.01537;,
 -4.48650;-7.83640;37.57967;,
 4.44540;-7.83640;37.33156;,
 3.94920;-7.83640;46.01537;,
 -4.48290;-7.83640;29.77787;,
 4.44930;-7.83640;29.52976;,
 13.87500;-7.83640;26.30476;,
 13.87140;-7.83640;34.10656;,
 21.81300;-7.83640;30.13637;,
 29.07030;-7.83640;21.51436;,
 22.24740;-7.83640;18.41296;,
 26.83350;-7.83640;12.13816;,
 33.65640;-7.83640;15.23956;,
 35.42820;-7.84540;5.30087;,
 45.50760;-7.84540;5.30087;,
 35.73840;-7.83640;-2.98663;,
 45.81780;-7.83640;-2.98663;,
 28.60500;-7.83640;-2.21114;,
 26.04900;-7.83640;-12.20503;,
 33.18210;-7.83640;-12.98024;,
 29.69070;-7.83640;-20.50934;,
 18.58770;-7.83640;-21.71894;,
 21.31680;-7.83640;-27.42524;,
 13.37730;-7.83640;-31.89134;,
 11.14440;-7.83640;-26.68094;,
 3.91500;-7.83640;-28.99963;,
 6.14790;-7.83640;-34.21004;,
 4.44540;-7.83640;-46.03364;,
 -5.23080;-7.83640;-34.62044;,
 -4.98270;-7.83640;-45.53744;,
 -6.47160;-7.83640;-28.16984;,
 -14.23650;-7.83640;-25.70263;,
 -12.99600;-7.83640;-32.15353;,
 -21.35820;-7.83640;-28.66604;,
 -18.62880;-7.83640;-21.96704;,
 -26.04450;-7.83640;-14.13974;,
 -28.77360;-7.83640;-20.83874;,
 -33.26730;-7.83640;-14.77184;,
 -29.18100;-7.83640;-2.81503;,
 -36.27540;-7.83640;-3.06913;,
 -45.67290;-7.83640;-3.06913;,
 -36.24480;-7.83640;5.32517;,
 -45.67290;-7.83640;5.57327;,
 -29.27850;-7.83640;6.07127;,
 -34.75620;-7.83640;15.49756;,
 -27.56101;-7.83640;13.76086;,
 -29.54580;-7.83640;22.94117;,
 -23.09490;-7.83640;19.21937;,
 -15.37860;-7.83640;25.96126;,
 -21.82950;-7.83640;29.68306;,
 -14.90730;-7.83640;34.60216;,
 2.14140;8.42360;-9.31484;,
 5.27340;8.42360;-7.33664;,
 5.27340;-7.83640;-7.33664;,
 2.14140;-7.83640;-9.31484;,
 8.88270;8.42360;-2.29454;,
 8.89080;-7.83400;-2.28614;,
 8.19930;8.42360;5.20037;,
 8.19930;-7.83640;5.20037;,
 3.85500;8.42360;9.69287;,
 3.85500;-7.83640;9.69287;,
 -0.25830;8.42360;10.35497;,
 -0.25830;-7.83640;10.35497;,
 -5.56800;-7.83640;9.12136;,
 -5.56800;8.42360;9.12136;,
 -9.60390;-7.83640;4.70177;,
 -9.60390;8.42360;4.70177;,
 -9.69270;8.42360;-0.05683;,
 -9.69270;-7.83640;-0.05683;,
 -9.27570;-7.83640;-4.66514;,
 -9.27570;8.42360;-4.66514;,
 -3.78720;-7.83640;-8.47544;,
 -3.78720;8.42360;-8.47544;,
 59.60880;-7.83010;-2.45774;,
 59.29860;-7.83910;5.82977;,
 59.60880;8.42990;-2.45774;,
 59.29860;8.42091;5.43977;,
 -5.70810;-7.83640;-59.31973;,
 3.72000;-7.83640;-59.81594;,
 -5.70810;8.42360;-59.31973;,
 3.72000;8.42360;-59.81594;,
 -59.47410;-7.83640;5.57327;,
 -59.47410;-7.83640;-3.06913;,
 -59.47410;8.42360;5.57327;,
 -59.47410;8.42360;-3.06913;,
 3.94920;-7.83640;59.81657;,
 -4.73460;-7.83640;59.81657;,
 3.94920;8.42360;59.81657;,
 -4.73460;8.42360;59.81657;;
 
 171;
 4;0,1,2,3;,
 4;2,4,5,3;,
 4;2,6,7,4;,
 3;7,6,8;,
 3;8,9,7;,
 3;7,9,10;,
 4;9,11,12,10;,
 3;12,11,13;,
 4;14,15,16,13;,
 3;12,13,16;,
 3;16,17,12;,
 4;16,18,19,17;,
 3;19,18,20;,
 3;21,19,20;,
 3;21,20,22;,
 3;22,23,21;,
 3;24,21,23;,
 4;23,25,26,24;,
 4;27,28,29,25;,
 3;25,29,26;,
 3;30,26,29;,
 4;29,31,32,30;,
 3;32,31,33;,
 3;34,32,33;,
 4;33,35,36,34;,
 3;36,35,37;,
 4;37,38,39,36;,
 4;40,41,42,38;,
 4;42,43,39,38;,
 3;44,43,42;,
 3;43,44,45;,
 3;45,44,46;,
 3;47,45,46;,
 4;46,48,49,47;,
 3;48,50,49;,
 3;5,49,50;,
 3;5,50,3;,
 4;51,52,53,54;,
 4;53,52,55,56;,
 4;53,56,57,58;,
 3;57,59,58;,
 3;59,57,60;,
 3;57,61,60;,
 4;60,61,62,63;,
 3;62,64,63;,
 4;65,64,66,67;,
 3;62,66,64;,
 3;66,62,68;,
 4;66,68,69,70;,
 3;69,71,70;,
 3;72,71,69;,
 3;72,73,71;,
 3;73,72,74;,
 3;75,74,72;,
 4;74,75,76,77;,
 4;78,77,79,80;,
 3;77,76,79;,
 3;81,79,76;,
 4;79,81,82,83;,
 3;82,84,83;,
 3;85,84,82;,
 4;84,85,86,87;,
 3;86,88,87;,
 4;88,86,89,90;,
 4;91,90,92,93;,
 4;92,90,89,94;,
 3;95,92,94;,
 3;94,96,95;,
 3;96,97,95;,
 3;98,97,96;,
 4;97,98,99,100;,
 3;100,99,101;,
 3;55,101,99;,
 3;55,52,101;,
 4;53,58,6,2;,
 4;1,54,53,2;,
 4;59,60,9,8;,
 4;63,64,13,11;,
 4;64,65,14,13;,
 4;16,66,70,18;,
 4;15,67,66,16;,
 4;71,73,22,20;,
 4;77,78,27,25;,
 4;74,77,25,23;,
 4;28,80,79,29;,
 4;79,83,31,29;,
 4;38,37,88,90;,
 4;91,40,38,90;,
 4;87,35,33,84;,
 4;42,41,93,92;,
 4;44,42,92,95;,
 4;48,46,97,100;,
 4;50,101,52,3;,
 4;51,0,3,52;,
 4;102,103,21,24;,
 4;104,105,75,72;,
 4;104,103,102,105;,
 4;103,106,19,21;,
 4;107,104,72,69;,
 4;107,106,103,104;,
 4;106,108,12,17;,
 4;109,107,68,62;,
 4;109,108,106,107;,
 4;108,110,7,10;,
 4;111,109,61,57;,
 4;110,108,109,111;,
 4;110,112,4,7;,
 4;113,111,57,56;,
 4;112,110,111,113;,
 4;114,113,55,99;,
 4;112,115,49,5;,
 4;112,113,114,115;,
 4;116,114,99,98;,
 4;115,117,47,49;,
 4;115,114,116,117;,
 4;117,118,39,43;,
 4;119,116,94,89;,
 4;118,117,116,119;,
 4;120,119,89,86;,
 4;118,121,36,39;,
 4;119,120,121,118;,
 4;122,120,86,85;,
 4;121,123,34,36;,
 4;120,122,123,121;,
 4;105,122,81,76;,
 4;123,102,26,30;,
 4;122,105,102,123;,
 3;108,10,12;,
 3;109,62,61;,
 3;123,32,34;,
 3;116,98,96;,
 3;117,45,47;,
 3;117,43,45;,
 3;102,24,26;,
 3;105,76,75;,
 3;122,85,82;,
 3;116,96,94;,
 3;123,30,32;,
 3;122,82,81;,
 3;107,69,68;,
 3;106,17,19;,
 3;112,5,4;,
 3;113,56,55;,
 4;33,31,83,84;,
 4;35,87,88,37;,
 4;44,95,97,46;,
 4;48,100,101,50;,
 4;6,58,59,8;,
 4;60,63,11,9;,
 4;73,74,23,22;,
 4;20,18,70,71;,
 4;124,125,65,67;,
 4;126,124,67,15;,
 4;127,126,15,14;,
 4;125,127,14,65;,
 4;125,124,126,127;,
 4;128,129,78,80;,
 4;130,128,80,28;,
 4;131,130,28,27;,
 4;129,131,27,78;,
 4;129,128,130,131;,
 4;132,133,91,93;,
 4;134,132,93,41;,
 4;135,134,41,40;,
 4;133,135,40,91;,
 4;133,132,134,135;,
 4;136,137,51,54;,
 4;138,136,54,1;,
 4;139,138,1,0;,
 4;137,139,0,51;,
 4;137,136,138,139;;
 
 MeshMaterialList {
  2;
  171;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  78;
  0.000000;1.000000;0.000000;,
  0.000184;1.000000;-0.000404;,
  0.000407;1.000000;0.000069;,
  0.000814;1.000000;0.000517;,
  -0.000250;0.999999;0.001130;,
  0.000518;1.000000;0.000590;,
  0.000000;-1.000000;-0.000000;,
  -0.000190;-1.000000;0.000419;,
  -0.000402;-1.000000;-0.000081;,
  -0.000783;-1.000000;-0.000469;,
  0.000249;-0.999999;-0.001077;,
  -0.000492;-1.000000;-0.000561;,
  -0.000046;-1.000000;-0.000034;,
  -0.000015;-1.000000;0.000047;,
  0.000008;-1.000000;0.000034;,
  -0.000020;-1.000000;-0.000055;,
  -0.000045;-1.000000;0.000023;,
  0.000024;-1.000000;0.000102;,
  1.000000;0.000000;0.000000;,
  -0.000500;0.999999;0.001120;,
  0.038323;0.000000;-0.999265;,
  -0.998618;0.000000;0.052560;,
  0.000000;-0.000000;1.000000;,
  0.000498;-0.999999;-0.001067;,
  0.323716;0.000000;0.946154;,
  0.386304;0.000000;0.922372;,
  0.999593;0.000000;0.028536;,
  0.998371;0.000000;0.057048;,
  0.618913;0.000000;0.785459;,
  0.786665;0.000000;0.617380;,
  0.920221;0.001041;0.391398;,
  0.985045;0.002028;0.172288;,
  0.000000;0.023978;0.999712;,
  -0.019165;0.023974;0.999529;,
  0.968807;0.000000;-0.247815;,
  0.941980;0.000000;-0.335668;,
  0.019165;0.000000;-0.999816;,
  0.000000;0.000000;-1.000000;,
  0.791622;0.000000;-0.611011;,
  0.565768;0.000000;-0.824564;,
  0.989792;0.000000;-0.142522;,
  0.995222;0.000000;-0.097641;,
  0.399879;0.000000;-0.916568;,
  0.305408;0.000000;-0.952222;,
  -0.999889;0.000000;0.014931;,
  -0.999742;0.000000;-0.022720;,
  -0.302775;0.000000;-0.953062;,
  -0.344177;0.000000;-0.938905;,
  -0.968516;0.000000;-0.248950;,
  -0.902801;0.000000;-0.430058;,
  -0.766162;0.000000;-0.642648;,
  -0.567749;0.000000;-0.823202;,
  0.026306;0.000000;0.999654;,
  0.013154;0.000000;0.999914;,
  -0.929401;0.000000;0.369072;,
  -0.989462;0.000000;0.144795;,
  -0.619389;0.000000;0.785084;,
  -0.744038;0.000000;0.668138;,
  -0.433224;0.000000;0.901286;,
  -0.274732;0.000000;0.961521;,
  -0.999892;0.000000;-0.014701;,
  -0.999568;0.000000;-0.029398;,
  -0.686280;-0.000027;0.727337;,
  -0.209774;0.000000;0.977750;,
  -0.965107;-0.000173;0.261857;,
  -0.908935;-0.000144;-0.416937;,
  -0.462561;0.000000;-0.886587;,
  0.034335;0.000000;-0.999410;,
  0.505113;0.000000;-0.863053;,
  0.928904;0.000000;-0.370321;,
  0.999359;0.000000;0.035784;,
  0.864271;0.000000;0.503027;,
  0.365107;0.000000;0.930966;,
  -0.038323;0.023961;0.998978;,
  0.999265;0.000449;0.038325;,
  0.998618;0.000000;-0.052560;,
  -0.052558;0.000000;-0.998618;,
  -1.000000;0.000000;0.000000;;
  171;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,1,2,0;,
  3;2,1,3;,
  4;4,4,5,3;,
  3;2,3,5;,
  3;5,0,2;,
  4;5,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  4;6,6,8,7;,
  3;8,9,7;,
  4;10,9,11,10;,
  3;8,11,9;,
  3;11,8,12;,
  4;11,12,13,6;,
  3;13,6,6;,
  3;14,6,13;,
  3;14,6,6;,
  3;6,14,6;,
  3;6,6,14;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  4;6,6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  4;6,6,6,6;,
  3;6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  4;6,6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  4;24,25,25,24;,
  4;26,26,27,27;,
  4;28,29,29,28;,
  4;30,31,31,30;,
  4;32,33,33,32;,
  4;34,34,35,35;,
  4;36,36,37,37;,
  4;38,39,39,38;,
  4;40,41,41,40;,
  4;42,43,43,42;,
  4;44,44,45,45;,
  4;46,47,47,46;,
  4;48,49,49,48;,
  4;37,37,37,37;,
  4;50,50,51,51;,
  4;52,53,53,52;,
  4;54,55,55,54;,
  4;56,57,57,56;,
  4;58,58,59,59;,
  4;60,60,61,61;,
  4;0,0,0,0;,
  4;17,6,6,14;,
  4;62,62,63,63;,
  4;0,0,0,0;,
  4;16,17,14,13;,
  4;64,64,62,62;,
  4;0,0,2,0;,
  4;15,16,12,8;,
  4;65,65,64,64;,
  4;0,0,0,0;,
  4;6,15,6,6;,
  4;66,65,65,66;,
  4;0,0,0,0;,
  4;6,6,6,6;,
  4;67,66,66,67;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;67,67,68,68;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;68,68,69,69;,
  4;0,0,0,0;,
  4;6,6,6,6;,
  4;70,69,69,70;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;70,71,71,70;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;71,72,72,71;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;72,63,63,72;,
  3;0,0,2;,
  3;15,8,6;,
  3;0,0,0;,
  3;6,6,6;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;0,0,0;,
  3;6,6,6;,
  3;16,13,12;,
  3;0,0,0;,
  3;0,0,0;,
  3;6,6,6;,
  4;51,47,47,51;,
  4;50,50,49,49;,
  4;54,54,57,57;,
  4;56,56,58,58;,
  4;25,25,28,28;,
  4;29,30,30,29;,
  4;39,42,42,39;,
  4;38,35,35,38;,
  4;23,23,10,10;,
  4;20,20,36,36;,
  4;19,19,4,4;,
  4;73,73,33,33;,
  4;74,74,74,74;,
  4;6,6,6,6;,
  4;21,21,44,44;,
  4;0,0,0,0;,
  4;75,75,41,41;,
  4;76,76,76,76;,
  4;6,6,6,6;,
  4;22,22,53,53;,
  4;0,0,0,0;,
  4;37,37,37,37;,
  4;77,77,77,77;,
  4;6,6,6,6;,
  4;18,18,26,26;,
  4;0,0,0,0;,
  4;77,77,60,60;,
  4;22,22,22,22;;
 }
 MeshTextureCoords {
  140;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
