import FWCore.ParameterSet.Config as cms

process = cms.Process("TotoAna")

# Keep the logging output to a nice level
process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.MessageLogger = cms.Service("MessageLogger",
#	cout = cms.untracked.PSet(
#		default = cms.untracked.PSet(
#			limit = cms.untracked.int32(100)
#		),
#		threshold = cms.untracked.string('INFO')
#   ),
#	destinations = cms.untracked.vstring('cout')
#)

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

# Needed for GlobalPositionRcd
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
# For 3_3_6_patch4
#process.GlobalTag.globaltag = 'GR09_P_V8::All'
# For 3_4_2
#process.GlobalTag.globaltag = 'GR10_P_V1::All'
# For 3_5_4
#process.GlobalTag.globaltag = 'GR10_P_V2::All'
# For MC 356
process.GlobalTag.globaltag = 'START3X_V26_S09::All'

# Global geometry
#process.load("Configuration.StandardSequences.Geometry_cff")
#process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')

# Transient Track Builder
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")

# Geometry needed for clustering and calo shapes variables
# process.load("RecoEcal.EgammaClusterProducers.geometryForClustering_cff")

# ES cluster for pi0 discrimination variables
#process.load("RecoEcal.EgammaClusterProducers.preshowerClusterShape_cfi")

# pi0 discrimination variables
#process.load("RecoEcal.EgammaClusterProducers.piZeroDiscriminators_cfi")


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)


process.source = cms.Source("PoolSource",

# RECO
fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/c/ccecal/BEAM/Skims/InterestingEvents/bit40or41skim_minBiasRECO_run130910.root')
# fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/h/hbrun/BSCSkim_MinBiasFilter/data/BSCFilter_Jan29_v8_MinBiasFilter_Run123596_88.root')
#	fileNames = cms.untracked.vstring(
#   'file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValH130GGgluonfusion__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__104E25AC-CC78-DE11-AE55-001D09F2447F.root'
#   ,'file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValH130GGgluonfusion__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__748489A8-CC78-DE11-991C-000423D99896.root'
#   )
)

process.totoana = cms.EDAnalyzer("TotoAnalyzer",
	myConfig = cms.PSet(

		# Data type of the PoolSource ( RECO / PAT )
		dataType = cms.untracked.string("RECO"),   # use reco::Objects
		#dataType = cms.untracked.string("PAT"),    # use pat::Objects

		# Verbosite
		# 		0 = muet
 		# 		1 = No evts tous les 10 ou 100 evts
		# 		2 = Indique fonctions executees et nb d'objets reconstruits
 		# 		3 = Liste objets de haut niveau (electrons, muons, photons...)
 		# 		4 = Liste tous les objets (haut niveau, clusters....)
		# 		5 = Debug
 		verbosity = cms.untracked.int32(1),

		# name of output root file
		RootFileName = cms.untracked.string('Test.root'),

		# DATASET Infos  (will be written in runTree for bookeeping)
		xsection = cms.untracked.double(0.674770994),
		description = cms.untracked.string('Le dataset pourri a Roberto'),

		# What is written to rootuple		    
		doL1 = cms.untracked.bool(True),
		doHLT = cms.untracked.bool(True),
		doMC = cms.untracked.bool(True),
		doPDFInfo = cms.untracked.bool(True),
		doSignalMuMuGamma = cms.untracked.bool(False),  # not tested in 2.X.X or 3.X.X
		doSignalTopTop = cms.untracked.bool(False),
		signalGenerator = cms.untracked.string('PYTHIA'),
#		signalGenerator = cms.untracked.string('COMPHEP'),
#		signalGenerator = cms.untracked.string('ALPGEN'),
#		signalGenerator = cms.untracked.string('MADGRAPH'),
		doPhotonConversionMC = cms.untracked.bool(True),
		
		doPhotonMC = cms.untracked.bool(True),
		doElectronMC = cms.untracked.bool(True),
		doMuonMC = cms.untracked.bool(True),
		doJetMC = cms.untracked.bool(True),
		doMETMC = cms.untracked.bool(True),
		doUnstablePartsMC = cms.untracked.bool(True),
		
		doBeamSpot = cms.untracked.bool(True),
		doPrimaryVertex = cms.untracked.bool(True),
		doZeePrimaryVertex = cms.untracked.bool(False),
		doTrack = cms.untracked.bool(True),
		doJet = cms.untracked.bool(True),
		doMuon = cms.untracked.bool(True),
		doElectron = cms.untracked.bool(True),
		doPhoton = cms.untracked.bool(True),
		doCluster = cms.untracked.bool(True),
		keepClusterizedEcalRecHits = cms.untracked.bool(True),
		keepAllEcalRecHits = cms.untracked.bool(False),
		doMET = cms.untracked.bool(True),
		doBardak = cms.untracked.bool(True),
		
		doPhotonVertexCorrection = cms.untracked.bool(False),
		doPhotonIsolation = cms.untracked.bool(True),
		doPhotonConversion = cms.untracked.bool(True),
		conversionLikelihoodWeightsFile = cms.untracked.string('RecoEgamma/EgammaTools/data/TMVAnalysis_Likelihood.weights.txt'),

		# Draw MC particle tree
		drawMCTree = cms.untracked.bool(False),
		mcTreePrintP4 = cms.untracked.bool(True),
		mcTreePrintPtEtaPhi = cms.untracked.bool(False),
		mcTreePrintVertex = cms.untracked.bool(False),
		mcTreePrintStatus = cms.untracked.bool(True),
		mcTreePrintIndex = cms.untracked.bool(True),
		mcTreeStatus = cms.untracked.vint32( 1,2,3 ),	# accepted status codes

		# MC particles acceptance cuts
		photonMC_etaMax = cms.double(3.0),
		photonMC_ptMin = cms.double(2.0),
		electronMC_etaMax = cms.double(3.0),
		electronMC_ptMin = cms.double(2.0),
		muonMC_etaMax = cms.double(3.0),
		muonMC_ptMin = cms.double(0.0),
		jetMC_etaMax = cms.double(10.0),
		jetMC_ptMin = cms.double(0.0),

		# Photon isolation
		basicClustersIsolation_BarrelBC_type = cms.int32(210),                  # Type of Clusters used for isolation in barrel (see TRootCluster.h for type definition)
		basicClustersIsolation_EndcapBC_type = cms.int32(320),                  # Type of Clusters used for isolation in endcap (see TRootCluster.h for type definition)
		basicClustersIsolation_DRmax = cms.double(0.3),                         # size of the DR cone around photon - Et of BC in this cone are added
		basicClustersIsolation_ClusterEt_threshold = cms.double(0.0),           # Et threshold for BC added in DR cone
		basicClustersDoubleConeIsolation_BarrelBC_type = cms.int32(210),        # Type of Clusters used for isolation in barrel (see TRootCluster.h for type definition)
		basicClustersDoubleConeIsolation_EndcapBC_type = cms.int32(320),        # Type of Clusters used for isolation in endcap (see TRootCluster.h for type definition)
		basicClustersDoubleConeIsolation_DRmin = cms.double(0.05),              # size of the inner DR cone around photon - BC in this cone are rejected
		basicClustersDoubleConeIsolation_DRmax = cms.double(0.3),               # size of the outer DR cone around photon - Et of BC with DRmin < DR < DRmax are added
		basicClustersDoubleConeIsolation_ClusterEt_threshold = cms.double(0.0), # Et threshold for BC added in DR cone
		hcalRecHitIsolation_DRmax = cms.double(0.3),                            # size of the DR cone around photon - Et of HCAL rechits in this cone are added
		hcalRecHitIsolation_HitEt_threshold = cms.double(0.0),                  # Et threshold for HCAL rechits in DR cone
		trackerIsolation_DRmax = cms.double(0.3),                               # size of the DR cone around photon - pt of tracks in this cone are added
		trackerIsolation_pt_threshold = cms.double(0.0),                        # pt threshold for tracks added in DR cone
		trackerIsolation_pixelLayers_threshold = cms.int32(0),                  # minimum number of pixel layers with measurement required for tracks to be added in DR cone isolation

		# Parametrization of the Primary Vertex re-Reconstruction (used for Zee events)
		verbose = cms.untracked.bool(False),
		algorithm = cms.string('AdaptiveVertexFitter'),
		useBeamConstraint = cms.bool(True),
		
		PVSelParameters = cms.PSet(
			maxDistanceToBeam = cms.double(0.05), ## 200 / 500 microns if useBeamConstraint = true / false
			minVertexFitProb = cms.double(0.01) ## 1% vertex fit probability
		),
			
		TkFilterParameters = cms.PSet(
			maxNormalizedChi2 = cms.double(5.0),
			minSiliconHits = cms.int32(7), ## hits > 7
			maxD0Significance = cms.double(10.0), ## keep most primary tracks
			minPt = cms.double(0.0), ## better for softish events
			minPixelHits = cms.int32(1) ## hits > 2
		),

		VtxFinderParameters = cms.PSet(
		ptCut = cms.double(0.0),
		vtxFitProbCut = cms.double(0.01), ## 1% vertex fit probability
		trackCompatibilityToSVcut = cms.double(0.01), ## 1%
		trackCompatibilityToPVcut = cms.double(0.05), ## 5%
		maxNbOfVertices = cms.int32(0) ## search all vertices in each cluster
		),

		TkClusParameters = cms.PSet(
			zSeparation = cms.double(0.1) ## 1 mm max separation betw. clusters
		),
		
   ),

	producersNamesRECO = cms.PSet(
		dataType = cms.untracked.string("RECO"),
		allowMissingCollection = cms.untracked.bool(True),
		l1Producer = cms.InputTag("gtDigis"),
		hltProducer = cms.InputTag("TriggerResults","","HLT"),
		genParticlesProducer = cms.InputTag("genParticles"),
		genJetsProducer = cms.InputTag("iterativeCone5GenJets"),
		genMETsProducer = cms.InputTag("genMetCalo"),
		#genMETsProducer = cms.InputTag("genMetTrue"),
		beamSpotProducer = cms.InputTag("offlineBeamSpot"),
		primaryVertexProducer = cms.InputTag("offlinePrimaryVerticesWithBS"),
		trackProducer = cms.InputTag("generalTracks"),
		jetProducer = cms.InputTag("ak5CaloJets"),
		muonProducer = cms.InputTag("muons"),
		electronProducer = cms.InputTag("gsfElectrons"),
		photonProducer = cms.InputTag("photons"),
		metProducer = cms.InputTag("met"),
		barrelEcalRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
		endcapEcalRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
		reducedBarrelEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
		reducedEndcapEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),
		hbheRecHitProducer = cms.InputTag("hbhereco"),
		hoRecHitProducer = cms.InputTag("horeco"),
		hfRecHitProducer = cms.InputTag("hfreco")
	),

	producersNamesPAT = cms.PSet(
		dataType = cms.untracked.string("PAT"),
		allowMissingCollection = cms.untracked.bool(True),
		patEncapsulation = cms.untracked.bool(False),
		l1Producer = cms.InputTag("gtDigis"),
		hltProducer = cms.InputTag("TriggerResults","","HLT"),
		genParticlesProducer = cms.InputTag("genParticles"),
		genJetsProducer = cms.InputTag("iterativeCone5GenJets"),
		genMETsProducer = cms.InputTag("genMet"),
		beamSpotProducer = cms.InputTag("offlineBeamSpot"),
		#primaryVertexProducer = cms.InputTag("offlinePrimaryVerticesWithBS"),
		primaryVertexProducer = cms.InputTag("offlinePrimaryVertices"),
		trackProducer = cms.InputTag("generalTracks"),
		jetProducer = cms.InputTag("selectedLayer1Jets"),
		muonProducer = cms.InputTag("selectedLayer1Muons"),
		electronProducer = cms.InputTag("selectedLayer1Electrons"),
		photonProducer = cms.InputTag("selectedLayer1Photons"),
		metProducer = cms.InputTag("selectedLayer1METs"),
		barrelEcalRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
		endcapEcalRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
		reducedBarrelEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
		reducedEndcapEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),
		hbheRecHitProducer = cms.InputTag("hbhereco"),
		hoRecHitProducer = cms.InputTag("horeco"),
		hfRecHitProducer = cms.InputTag("hfreco")
	)
 )


##process.hltHighLevel = cms.EDFilter("HLTHighLevel",
##    HLTPaths = cms.vstring('HLT2PhotonRelaxed'),
##    andOr = cms.bool(True),
##    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
##)


# TotoAna standalone
process.p = cms.Path(process.totoana)

# Photon reReco + TotoAna
#process.load("photonReReco")
#process.p = cms.Path(process.photons*process.photonIDSequence*process.totoana)

# Pi0disc + TotoAna
#process.p = cms.Path(process.preshowerClusterShape*process.piZeroDiscriminators*process.totoana)

