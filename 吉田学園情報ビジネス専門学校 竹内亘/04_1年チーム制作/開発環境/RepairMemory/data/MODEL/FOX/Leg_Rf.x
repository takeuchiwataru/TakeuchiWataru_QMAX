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
 44;
 -5.10978;9.76784;7.29907;,
 -2.27162;8.76982;14.91431;,
 -2.42588;11.76387;11.17000;,
 -2.87141;12.76188;7.42504;,
 -2.50943;12.38760;4.80310;,
 -2.40564;9.01934;1.43101;,
 -2.27214;5.24934;-0.45726;,
 -4.50845;5.40155;3.17753;,
 -2.10737;0.79103;-1.94321;,
 -4.35172;1.28472;2.30208;,
 -1.96336;-2.83419;-2.06094;,
 -4.17545;-3.20631;1.92589;,
 -1.79893;-6.70791;-1.03929;,
 -4.44689;-7.19837;5.54497;,
 -1.58575;-11.59449;0.87281;,
 -3.41431;-11.68943;5.04392;,
 -4.42609;5.15202;11.04274;,
 -2.06546;4.27878;17.78412;,
 -4.25446;1.03523;11.79029;,
 -1.89458;0.03721;17.90738;,
 -4.06659;-4.20433;9.41629;,
 -1.70746;-5.32710;14.90910;,
 -1.63059;-7.82213;12.41126;,
 -1.52106;-11.19043;9.66340;,
 -5.47862;5.27679;6.54833;,
 -5.12719;-3.70534;5.67109;,
 -5.61303;0.78572;6.29698;,
 -0.04776;-11.18704;9.66465;,
 -0.14091;-7.76962;12.41350;,
 -0.17962;-5.22438;14.91237;,
 -0.32056;0.16301;17.91116;,
 -0.45593;4.47482;17.78929;,
 -0.65090;9.01417;14.92046;,
 -1.15314;11.85604;11.09252;,
 -1.61138;12.83884;7.36340;,
 -1.25308;12.41049;4.78246;,
 -1.10276;9.03598;1.40277;,
 -0.92036;5.28574;-0.47291;,
 -0.77049;0.85582;-1.88696;,
 -0.70623;-2.73439;-1.96618;,
 -0.60187;-6.56315;-0.95154;,
 -0.34341;-11.54471;0.99409;,
 1.30522;-11.73342;5.19996;,
 -0.11204;-0.51571;6.81546;;
 
 44;
 4;0,1,2,3;,
 4;3,4,5,0;,
 4;5,6,7,0;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;0,16,17,1;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,13,22,21;,
 4;13,15,23,22;,
 3;0,24,16;,
 3;7,24,0;,
 3;20,25,13;,
 3;25,11,13;,
 4;18,26,25,20;,
 4;26,9,11,25;,
 4;24,26,18,16;,
 4;24,7,9,26;,
 4;23,27,28,22;,
 4;22,28,29,21;,
 4;21,29,30,19;,
 4;19,30,31,17;,
 4;17,31,32,1;,
 4;2,1,32,33;,
 4;2,33,34,3;,
 4;3,34,35,4;,
 4;4,35,36,5;,
 4;5,36,37,6;,
 4;6,37,38,8;,
 4;8,38,39,10;,
 4;10,39,40,12;,
 4;12,40,41,14;,
 4;14,41,42,15;,
 4;23,15,42,27;,
 4;35,34,33,43;,
 4;43,37,36,35;,
 4;33,32,31,43;,
 4;31,30,29,43;,
 4;43,39,38,37;,
 4;29,28,27,43;,
 4;27,42,41,43;,
 4;41,40,39,43;;
 
 MeshMaterialList {
  9;
  44;
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.350000;0.350000;0.350000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "22679000120.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "thDW0G3HBL.jpg";
   }
  }
  Material {
   0.568400;0.568400;0.568400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.467200;0.006400;0.028000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.710000;0.710000;0.710000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
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
   TextureFilename {
    "fox_up.jpg";
   }
  }
 }
 MeshNormals {
  61;
  -0.501917;0.864441;0.028661;,
  -0.344687;0.831231;0.436172;,
  -0.543288;0.574505;0.612195;,
  -0.957376;0.287269;-0.030115;,
  -0.331241;0.831497;-0.445973;,
  -0.484409;0.547397;-0.682425;,
  -0.912675;0.131782;-0.386856;,
  -0.493576;0.320897;-0.808336;,
  -0.921151;0.023331;-0.388505;,
  -0.870687;0.047879;-0.489501;,
  -0.923431;-0.112286;-0.366972;,
  -0.880946;-0.116316;-0.458700;,
  -0.969292;-0.244318;-0.027947;,
  -0.888988;-0.199786;-0.412051;,
  -0.969677;-0.244025;-0.013359;,
  -0.904440;-0.175297;-0.388921;,
  -0.932778;0.083033;0.350759;,
  -0.954942;0.054429;0.291759;,
  -0.933714;-0.103307;0.342792;,
  -0.952410;-0.084888;0.292763;,
  -0.905115;-0.266698;0.331118;,
  -0.932182;-0.217787;0.289147;,
  -0.888743;-0.303112;0.343888;,
  -0.889437;-0.276143;0.364207;,
  -0.998221;0.054480;-0.024204;,
  -0.989711;-0.142471;-0.013198;,
  -0.999157;-0.035082;-0.021307;,
  0.022841;-0.667115;0.744605;,
  0.002989;-0.875686;0.482871;,
  0.034550;-0.600233;0.799079;,
  0.014579;-0.237337;0.971318;,
  -0.042092;0.290941;0.955815;,
  -0.074042;0.670437;0.738263;,
  -0.061374;0.893421;0.445009;,
  -0.048149;0.997446;0.052753;,
  -0.036039;0.889904;-0.454722;,
  -0.024392;0.584349;-0.811136;,
  -0.010562;0.379529;-0.925120;,
  0.029970;0.171453;-0.984736;,
  0.077475;-0.112246;-0.990656;,
  0.102536;-0.304828;-0.946872;,
  0.108019;-0.357478;-0.927654;,
  0.005464;-0.998874;0.047135;,
  0.997875;0.060009;-0.025398;,
  0.016302;-0.999594;-0.023359;,
  0.995401;0.094588;-0.015179;,
  0.993721;0.110986;0.014162;,
  0.995627;0.093319;-0.004221;,
  0.996704;0.057672;-0.057048;,
  0.995953;0.078083;-0.044504;,
  0.996883;0.075591;-0.022603;,
  0.998753;0.049847;-0.002646;,
  0.999561;0.024051;0.017313;,
  0.999739;0.015970;0.016346;,
  0.997067;0.026003;-0.071978;,
  0.996883;0.037228;-0.069560;,
  0.999851;0.007889;0.015378;,
  0.997516;0.069467;-0.011671;,
  0.990664;0.130730;-0.038668;,
  0.995731;0.072887;-0.056632;,
  0.997120;0.014774;-0.074387;;
  44;
  4;3,2,1,0;,
  4;0,4,5,3;,
  4;5,7,6,3;,
  4;7,9,8,6;,
  4;9,11,10,8;,
  4;11,13,12,10;,
  4;13,15,14,12;,
  4;3,17,16,2;,
  4;17,19,18,16;,
  4;19,21,20,18;,
  4;21,12,22,20;,
  4;12,14,23,22;,
  3;3,24,17;,
  3;6,24,3;,
  3;21,25,12;,
  3;25,10,12;,
  4;19,26,25,21;,
  4;26,8,10,25;,
  4;24,26,19,17;,
  4;24,6,8,26;,
  4;28,28,27,27;,
  4;27,27,29,29;,
  4;29,29,30,30;,
  4;30,30,31,31;,
  4;31,31,32,2;,
  4;1,2,32,33;,
  4;1,33,34,0;,
  4;0,34,35,4;,
  4;4,35,36,5;,
  4;5,36,37,7;,
  4;7,37,38,38;,
  4;38,38,39,39;,
  4;39,39,40,40;,
  4;40,40,41,41;,
  4;44,44,42,42;,
  4;28,42,42,28;,
  4;45,46,47,43;,
  4;43,48,49,45;,
  4;47,50,51,43;,
  4;51,52,53,43;,
  4;43,54,55,48;,
  4;53,56,57,43;,
  4;57,58,59,43;,
  4;59,60,54,43;;
 }
 MeshTextureCoords {
  44;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
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
