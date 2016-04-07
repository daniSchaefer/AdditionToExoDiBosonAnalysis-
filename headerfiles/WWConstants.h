#ifndef WWCONSTANTS_H
#define WWCONSTANTS_H

//constants for electron (W)
#define WWELEPT 120
#define WWELEECALGAPMIN 1.4442
#define WWELEECALGAPMAX 1.566
#define WWELEETA 2.5
#define WWELEPTLOOSE 35
#define WWELEISO 5

//constants for muon (W)
#define WWMUPT 53
#define WWMUETA 2.1
#define WWMUISO 0.1
#define WWMUPTLOOSE 20
#define WWMUETALOOSE 2.4
#define WWMUISOLOOSE 0.1

//constants for MET
#define WWMETPTMU 40
#define WWMETPTELE 80


//constants for jets
#define WWAK8JETPT 200
#define WWAK8JETETA 2.4
#define WWAK8JETDELTAR 1.0
#define WWAK8JETTAU21HIGHPURITY 0.60
#define WWAK8JETTAU21LOWPURITY 0.75
#define WWAK8JETMASSMIN 65
#define WWAK8JETMASSMAX 85

#define WZAK8JETMASSMIN 85
#define WZAK8JETMASSMAX 105

#define WWAK4JETPT 30
#define WWAK4JETETA 2.4
#define WWAK4JETDELTARLEPTON 0.3
#define WWAK4JETDELTARAK8JET 0.8
#define WWAK4JETBTAGGERMEDIUMWP 0.89

//constants for leptonic W
#define WWPTW 200

//constants for hadronic W
//-> same as for leptonic W

//constants for WW system
#define WWMASSMIN 700
#define WWMASSMAX 6000
#define WWDELTAPHIWHADMET  2
#define WWDELTAPHIWHADWLEP 2
#define WWDELTARWHADLEPTON TMath::Pi()/2.0

//constants for the WZ decay with leptonic Z and hadronic W
#define WZMUETASMALL 2.1
#define WZMUETABIG   2.4
#define WZMUPTSMALL 20
#define WZMUPTBIG  50

#define WZELETASMALL 2.5
#define WZELETABIG 2.5
#define WZELPTSMALL 35
#define WZELPTBIG 115

#define WZZMASSMAX 70
#define WZZMASSMIN 110



#endif