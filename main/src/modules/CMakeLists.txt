# Copyright: (C) 2014 WYSIWYD Consortium
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

#Add here modules without specific dependency
add_subdirectory(abm)
add_subdirectory(adaptiveLayer)
add_subdirectory(attentionRelated)
add_subdirectory(reactiveLayer)
add_subdirectory(contextualLayer)
add_subdirectory(learnPrimitive)
add_subdirectory(navigationRelated)
add_subdirectory(narrativeRelated)
add_subdirectory(opcRelated)
add_subdirectory(ppsAllostatic)
#add_subdirectory(reactiveLayerEFAA)
add_subdirectory(reservoir)
add_subdirectory(scenarioSpecific)
add_subdirectory(systemAuditory)
add_subdirectory(systemHaptic)
add_subdirectory(systemMotor)
add_subdirectory(tools)
add_subdirectory(samRelated)
add_subdirectory(jointsAwareness)
add_subdirectory(kinematicStructureLearning)

#Add modules with dependencies here
if(WYSIWYD_USE_OpenCV)
    add_subdirectory(systemVisual)
    add_subdirectory(visionRelated)
endif()

if(WYSIWYD_USE_OpenCV)
    add_subdirectory(bodySchema)
endif()

if(WYSIWYD_USE_kinectWrapper)
    add_subdirectory(humanUnderstanding)
endif()

if(WYSIWYD_USE_TUIO)
    add_subdirectory(reactableRelated)
endif()
