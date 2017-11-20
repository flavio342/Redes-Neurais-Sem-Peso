const int SIGNAL_SIZE = 32;
const int INPUT_SIZE = SIGNAL_SIZE*6;
const int BITS_PER_RAM = 25;
const int N_NEURONIOS = INPUT_SIZE/BITS_PER_RAM;
const int INPUT_FACTOR = 32;

const PROGMEM String labels[5] = {"front","idle","right","back","left"};
const PROGMEM int nNeuronios[] = {7};
const PROGMEM int nIndicesDeEntradas[] = {25};
const PROGMEM int indicesDeEntradas[5][7][25] = {{{25,162,146,49,95,86,125,151,17,5,161,82,145,0,85,137,44,182,173,7,6,104,180,72,42},{80,8,45,87,98,47,48,43,93,59,4,163,112,126,36,190,166,26,67,139,136,179,83,158,128},{61,114,170,160,99,113,10,50,152,78,32,107,134,130,70,84,101,150,102,73,94,9,13,138,189},{117,71,31,100,187,149,106,168,40,97,183,115,81,52,109,184,1,153,157,171,140,154,91,105,68},{15,169,110,33,89,79,58,57,108,122,121,75,11,37,28,120,172,155,148,159,39,165,129,18,3},{2,142,46,23,123,62,20,30,103,34,55,141,88,63,92,14,69,77,38,24,181,118,51,132,175},{12,16,35,156,53,147,143,124,56,191,174,116,54,133,76,127,65,135,21,64,188,178,66,177,60}},{{25,162,146,49,95,86,125,151,17,5,161,82,145,0,85,137,44,182,173,7,6,104,180,72,42},{80,8,45,87,98,47,48,43,93,59,4,163,112,126,36,190,166,26,67,139,136,179,83,158,128},{61,114,170,160,99,113,10,50,152,78,32,107,134,130,70,84,101,150,102,73,94,9,13,138,189},{117,71,31,100,187,149,106,168,40,97,183,115,81,52,109,184,1,153,157,171,140,154,91,105,68},{15,169,110,33,89,79,58,57,108,122,121,75,11,37,28,120,172,155,148,159,39,165,129,18,3},{2,142,46,23,123,62,20,30,103,34,55,141,88,63,92,14,69,77,38,24,181,118,51,132,175},{12,16,35,156,53,147,143,124,56,191,174,116,54,133,76,127,65,135,21,64,188,178,66,177,60}},{{25,162,146,49,95,86,125,151,17,5,161,82,145,0,85,137,44,182,173,7,6,104,180,72,42},{80,8,45,87,98,47,48,43,93,59,4,163,112,126,36,190,166,26,67,139,136,179,83,158,128},{61,114,170,160,99,113,10,50,152,78,32,107,134,130,70,84,101,150,102,73,94,9,13,138,189},{117,71,31,100,187,149,106,168,40,97,183,115,81,52,109,184,1,153,157,171,140,154,91,105,68},{15,169,110,33,89,79,58,57,108,122,121,75,11,37,28,120,172,155,148,159,39,165,129,18,3},{2,142,46,23,123,62,20,30,103,34,55,141,88,63,92,14,69,77,38,24,181,118,51,132,175},{12,16,35,156,53,147,143,124,56,191,174,116,54,133,76,127,65,135,21,64,188,178,66,177,60}},{{25,162,146,49,95,86,125,151,17,5,161,82,145,0,85,137,44,182,173,7,6,104,180,72,42},{80,8,45,87,98,47,48,43,93,59,4,163,112,126,36,190,166,26,67,139,136,179,83,158,128},{61,114,170,160,99,113,10,50,152,78,32,107,134,130,70,84,101,150,102,73,94,9,13,138,189},{117,71,31,100,187,149,106,168,40,97,183,115,81,52,109,184,1,153,157,171,140,154,91,105,68},{15,169,110,33,89,79,58,57,108,122,121,75,11,37,28,120,172,155,148,159,39,165,129,18,3},{2,142,46,23,123,62,20,30,103,34,55,141,88,63,92,14,69,77,38,24,181,118,51,132,175},{12,16,35,156,53,147,143,124,56,191,174,116,54,133,76,127,65,135,21,64,188,178,66,177,60}},{{25,162,146,49,95,86,125,151,17,5,161,82,145,0,85,137,44,182,173,7,6,104,180,72,42},{80,8,45,87,98,47,48,43,93,59,4,163,112,126,36,190,166,26,67,139,136,179,83,158,128},{61,114,170,160,99,113,10,50,152,78,32,107,134,130,70,84,101,150,102,73,94,9,13,138,189},{117,71,31,100,187,149,106,168,40,97,183,115,81,52,109,184,1,153,157,171,140,154,91,105,68},{15,169,110,33,89,79,58,57,108,122,121,75,11,37,28,120,172,155,148,159,39,165,129,18,3},{2,142,46,23,123,62,20,30,103,34,55,141,88,63,92,14,69,77,38,24,181,118,51,132,175},{12,16,35,156,53,147,143,124,56,191,174,116,54,133,76,127,65,135,21,64,188,178,66,177,60}}};
const PROGMEM int nDados[5][7] = {{54,12,17,15,10,39,15},{10,12,6,2,2,6,4},{46,13,49,27,22,18,19},{31,28,52,39,12,13,12},{41,15,19,23,18,21,8}};
const PROGMEM long tabelaDeDadosKeys[5][7][54] = {{{12647283,8444787,13238263,31588211,13238135,8448883,13172735,15269759,14875519,8978295,29490039,13172727,12647287,9043959,14744447,8452983,15269887,14809971,25295731,15335295,8440691,14745459,13238271,14745463,32112503,13172607,29491059,14941047,12648319,14810999,14744439,8974199,14744435,8454007,9039731,8452979,15335415,12648311,15269879,8974195,12648307,15335283,14809975,15269751,8454003,9043831,15335423,14745471,15466495,15335287,14876671,13172599,13238143,12647295},{31090045,33449341,31352177,30565757,31352189,33187197,30565749,31090033,30565745,32662909,31090037,31352181,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{7396714,7659374,7659502,7396650,7790510,7790382,7789870,7659306,7658794,7659370,7790446,7658858,7659310,7659438,7790574,7396642,7658798,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{11522867,10719541,11260209,10735923,11243827,11262257,10735925,11243825,10736433,10719539,11245873,11508019,10735921,10721585,10719537,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{11024669,11020573,28850527,28850463,11024733,28850461,27801885,27801949,27801887,27801951,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{29406163,29733847,31761363,29471683,25207747,29402071,29483975,25207235,31830995,31826915,29467587,29668311,29467091,31761395,29402067,29401555,29729747,29467603,31761379,29401539,29729735,29668307,29402051,31830979,29467607,29471699,31826903,29664211,31826935,29733843,29746119,29402055,31765459,31826919,29467075,29483991,31765491,29467591,29664215,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{29642214,30166446,21777838,31215022,4476334,31219118,22826414,31284654,30166510,31215086,29642158,31219182,29642222,21253550,4476326,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},{{8448883,8440435,8448891,8448851,8452979,8440387,8440691,8440659,8440643,8452987,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{31090045,17982833,26371441,31090041,26240369,5399921,22177145,31090033,30565745,22177137,1205617,30565753,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{7396714,7363874,7396706,7363938,7396642,7396386,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{10719537,10715441,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{11020573,10496285,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{25207235,29401539,16818627,29467075,25272771,25207234,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{4476334,4214182,4476326,4476324,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},{{14876539,14867323,14876543,8444787,14867315,14744575,12647283,8448883,14941183,10550131,15400823,14875519,14736247,15269759,14875647,14736243,15269887,15400959,14942207,8440691,14811135,10541939,14810111,15400951,14745463,12770171,14876535,12647295,12639091,14744435,14744439,15269879,14875507,15269751,15400827,14942079,14744447,14745471,15466495,14875511,15400831,14875515,8452979,14876671,14745599,14744443,0,0,0,0,0,0,0,0},{31352185,33449341,31352177,22701437,22963569,31352189,31090041,22963573,31090033,30565745,22177137,31352181,22963581,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{7864302,7527778,7527786,7396834,7527906,7798766,7798762,7864298,7396706,7855530,7593442,7855534,7396650,7790570,7790382,7789870,7789866,7470562,7528290,7790446,7659370,7527914,7593962,7790574,7789998,7396642,7396714,7593954,7528418,7602154,7789930,7789934,7789994,7658858,7855598,7528426,7462370,7798634,7855594,7856110,7798638,7790442,7528298,7790058,7658794,7593450,7790062,7856106,7527850,0,0,0,0,0},{10981683,11524531,10983731,11508019,10715441,10721585,11524915,11243827,11508155,10719537,11525555,11245875,11525563,11246009,11506099,11505971,11508147,11243963,11243825,11245873,11525427,11524403,11509171,11246001,11241777,11506107,11246003,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{27801885,11413853,27801949,27801951,27933023,27933021,11024733,11086173,27867485,27932957,11090269,28195165,11155741,15280477,28195167,11151709,11155805,11024669,11020573,11417885,11020637,11417949,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{29401559,29418455,29467095,29401539,29401543,29467079,29483479,29418439,29483463,29467607,29402071,29483975,25207235,29402055,29467075,29417927,29483991,29467091,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{6053294,22371758,6049198,5000622,5000614,31219118,31284654,22306222,6118830,22896038,22896046,22830510,6049190,21253550,21777838,22826414,4476326,4476334,6053286,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},{{12778367,14867323,14876543,8444787,12647287,12647291,14744575,12639099,14745471,8454143,12647283,8448883,12647295,12639091,14875519,8452991,8440691,13172735,14875647,8448891,14744447,15269887,15400959,8452987,14875515,14736251,8452979,14876671,14745599,12647423,14744443,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{31090045,33449341,22701433,22181245,22701437,22963569,31352189,22181241,30565757,31090033,22967665,30565753,31356285,22963577,31352177,31356281,33453437,31094141,30565745,31090041,22177137,22701425,22177145,31352185,22967677,22963581,22705529,22967673,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{16318314,7527778,7536482,16711530,7527786,7864298,7527906,7404898,7405418,7798762,16317794,16318306,7397218,7397226,8388586,7536618,7863786,16449514,7593442,7929706,7536098,7601642,7536490,7535978,7659370,7396706,7601634,7535970,8060898,16711658,7396642,16449506,7396714,16317922,16514530,7602154,8125922,7667562,8126434,7798634,16449386,16515042,7528298,7798766,7405410,8060778,8060386,16777194,8323050,7536610,16448994,7798250,0,0},{11509179,10981683,11523891,10999091,11523379,11508019,10715441,11517235,10998067,28292403,11524915,28309299,10719539,11508155,10719537,11509043,11522355,11525939,11509171,11515187,10982707,11531571,11506995,11007795,11246009,11525427,11505971,11534131,11508147,27785011,28292531,11243827,11246001,10999603,11525555,11524403,11517371,28308787,11532083,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{11090269,15280477,11086109,15297373,11024669,11020573,11024733,11086173,15280413,11020637,15284573,15280989,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{29467095,29401539,29467079,29483479,29467607,29467091,25207235,29467099,29467083,25272787,29467075,29471191,29471187,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{6053294,6049198,4476334,22826414,4476326,22830510,5008814,4484526,6049190,21777838,5000622,6053286,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},{{14745599,8448883,8450047,8444787,8448887,8450039,9043967,8978431,12648447,13238263,8974327,14745471,8454143,12648311,8449919,13172595,8974199,11075583,8454007,8454015,8452979,8978295,8449911,8978291,12647287,8452983,8452991,8440691,8440703,13172735,8453119,8974335,8978303,15269887,8440831,8444799,12648319,8978423,13172599,13172727,8449023,0,0,0,0,0,0,0,0,0,0,0,0,0},{28468605,31090045,33449341,30565757,22177149,31352189,33187197,32662901,22177145,24274301,22177137,30565745,32662909,26371453,30565753,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{7396714,7798634,7659374,7396650,7798638,7659306,7397226,7404898,7405418,7397218,7790446,7658858,7659370,7396706,7667566,7405410,7667562,7396642,7659310,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{11785009,10981683,11785011,10735921,11785015,10735923,12048179,10998579,10715441,10735925,10982707,11260725,10719539,10719537,11522867,10998067,10719541,10999603,10736433,12047155,10736437,10736439,10736435,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{12069149,28850461,11086109,12069213,12073245,12138781,11090269,12073309,11024669,11020573,11090205,11024733,15280413,15284509,12138845,11020637,12134685,28850525,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{29406163,25211843,29401539,25212371,25211347,25276883,29406147,25211859,25207251,25277907,29405651,25207235,25211331,29471187,25272787,25277395,29467075,25272771,29471699,29401555,29467091,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{29642158,4476350,21777838,21253550,4476334,5000622,30166446,4476326,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}};
const PROGMEM int tabelaDeDadosValues[5][7][54]= {{{24,3,16,1,8,65,4,8,1,10,1,3,6,3,1,7,10,1,1,3,8,6,5,30,1,5,1,1,1,3,8,3,4,1,1,240,32,10,12,3,1,1,2,38,2,1,27,5,1,32,1,20,1,1},{190,139,1,13,193,16,3,23,79,12,14,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{10,92,2,79,1,44,1,30,187,32,93,13,78,2,8,10,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{2,2,7,1,1,2,2,21,4,1,9,1,14,13,604,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{178,219,15,19,6,5,103,60,17,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{11,11,3,1,2,14,1,17,1,2,17,2,2,3,20,1,2,69,3,314,1,16,32,1,18,28,1,2,2,8,1,12,9,1,46,2,2,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,122,67,1,307,2,1,3,43,1,32,2,10,78,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},{{83,9,3,2,3,3,409,93,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,136,33,1,1,1,8,2,71,343,4,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{3,4,91,1,350,159,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{130,478,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{603,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{524,6,1,62,13,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{77,8,513,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},{{1,1,35,49,6,1,27,11,4,1,4,50,4,1,11,57,9,48,6,34,14,3,3,1,9,1,1,2,7,99,57,1,14,2,1,1,18,10,1,13,8,7,53,39,13,4,0,0,0,0,0,0,0,0},{129,1,100,1,1,392,1,1,78,21,1,15,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{36,5,3,2,9,23,3,24,4,1,2,1,72,17,1,38,10,2,3,14,1,4,4,52,5,26,44,3,1,2,55,8,4,59,1,8,1,5,10,24,6,36,3,13,24,6,9,56,2,0,0,0,0,0},{5,1,1,104,14,46,1,2,12,289,5,26,1,1,1,4,29,1,5,140,2,30,3,10,1,1,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{4,2,31,4,12,15,198,4,4,2,23,6,1,1,1,6,25,56,236,2,99,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,3,64,247,38,82,79,26,26,22,3,1,4,6,28,31,75,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{54,3,27,89,1,10,39,5,49,1,75,79,1,2,49,32,16,209,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},{{1,6,4,24,1,25,19,9,2,1,16,28,70,4,13,9,53,2,5,1,30,54,73,12,9,1,91,44,44,2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{27,20,29,1,5,5,202,2,1,6,1,14,91,6,13,9,19,1,37,56,56,17,16,12,4,6,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,7,1,2,47,1,15,10,39,1,3,6,9,11,3,2,3,2,2,5,1,7,2,5,286,3,3,4,13,19,17,19,4,8,1,1,8,1,26,1,2,1,5,16,1,1,12,10,6,5,1,0,0},{4,54,25,4,20,1,4,2,7,6,2,3,41,2,283,17,1,39,14,8,6,2,26,1,1,30,15,2,2,2,1,1,1,3,13,5,1,1,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{33,115,5,2,4,342,9,38,2,29,78,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{163,89,22,1,1,123,14,4,3,1,233,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{15,34,284,14,19,3,18,1,1,14,256,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},{{1,160,9,4,27,1,1,85,4,1,7,1,8,8,4,2,2,5,7,6,67,5,15,2,7,25,8,38,2,111,3,79,2,43,2,1,5,6,6,22,14,0,0,0,0,0,0,0,0,0,0,0,0,0},{3,43,103,214,8,20,54,1,16,5,12,126,148,1,52,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{86,2,57,3,8,4,81,7,6,81,2,8,202,106,16,9,37,87,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,4,1,28,1,33,4,116,3,1,1,1,26,431,1,17,1,7,33,22,11,20,43,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{36,9,15,4,94,9,3,10,95,510,3,10,1,1,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{3,1,106,1,5,45,1,3,3,1,2,185,1,140,77,2,32,23,31,2,142,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{3,5,58,84,611,36,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}};


int definirBleachingDeUmaRede(int rede) {

  int somaHits = 0;
  int nHits = 0;
  for (int neuronio = 0; neuronio < pgm_read_word_near(nNeuronios); neuronio++) {
    for (int hit = 0; hit < pgm_read_word_near(&nDados[rede][neuronio]); hit++) {
      somaHits += pgm_read_word_near(&tabelaDeDadosValues[rede][neuronio][hit]);
      if (pgm_read_word_near(&tabelaDeDadosValues[rede][neuronio][hit]) > 0) {
        nHits++;
      }
    }
  }
  return somaHits / nHits;
}

int definirBleachingDasRedes() {

  int somaBleaching = 0;

  for (int i = 0; i < 5; i++) {
    somaBleaching += definirBleachingDeUmaRede(i);
  }
  return somaBleaching / 5;
}

long powered(int base, int expo){
  long result = 1;
  for(int i=0;i<expo;i++){
    result *= base;
  }
  return result;
}

long binConv(String binary)
{
  long decimal = 0;
  
  for (int counter = 0; counter < BITS_PER_RAM ; counter++)
  {
    if (binary[counter] == '1'){
      decimal += powered(2,BITS_PER_RAM - 1 - counter); 
    }
  }
  return decimal;
}

int testeDeEntrada(int rede, int* entrada, int limiteDoBleaching) {

  int resultado = 0;

  for (int neuronio = 0; neuronio < pgm_read_word_near(nNeuronios); neuronio++) {
    
    String tabelaKey = "";
    for (int indice = 0; indice < pgm_read_word_near(nIndicesDeEntradas); indice++) {
      if (entrada[pgm_read_word_near(&indicesDeEntradas[rede][neuronio][indice])] > 0) {
        tabelaKey += "1";
      } else {
        tabelaKey += "0";
      }
    }
    
    for (int dado = 0; dado < pgm_read_word_near(&nDados[rede][neuronio]); dado++) {
      if (binConv(tabelaKey) == pgm_read_dword(&tabelaDeDadosKeys[rede][neuronio][dado])) {
        if (pgm_read_word_near(&tabelaDeDadosValues[rede][neuronio][dado]) > limiteDoBleaching) {
          resultado++;
        }
      }
    }

  }
  return resultado;
}

String testarRedes(int limiteDoBleaching, int* entrada) {

  int melhorResultado = -1;
  String labelDoMelhorResultado = "";

  for (int rede = 0; rede < 5; rede++) {
    int resultado = testeDeEntrada(rede, entrada, limiteDoBleaching);
    if (resultado > melhorResultado) {
      melhorResultado = resultado;
      labelDoMelhorResultado = labels[rede];
    }
  }
  return labelDoMelhorResultado;
}



