////////////////////////////////////////////////////////////////////////////////
// Filename: MyScene.cpp
////////////////////////////////////////////////////////////////////////////////

/*
Author: Luke Dicken - Jones
Date: 13/12/2018
*/

#include "MyScene.h"


// All objects in a scene instance are set up in the constructor
MyScene::MyScene(ID3D11Device* device, ShaderManagerClass* shaderManager)
{
	ObjectClass* island = new ObjectClass(ObjectClass::ModelType::Model);
	island->SetDevice(device);
	island->SetShaderManager(shaderManager);
	island->SetModel("../Engine/data/Island/island.txt");
	island->SetTextures(L"../Engine/data/Island/sand.dds");
	island->SetTranslation(0.0f, -2.125f, 0.0f);
	island->SetScale(0.05f, 0.0125f, 0.05f);
	AddObject("Island", island);

	ObjectClass* towel = new ObjectClass(ObjectClass::ModelType::Model);
	towel->SetDevice(device);
	towel->SetShaderManager(shaderManager);
	towel->SetModel("../Engine/data/Beach towel/beach_towel.txt");
	towel->SetTextures(L"../Engine/data/Beach towel/beach_towel_diffuse.dds");
	towel->SetTranslation(-35.0f, -0.35f, 55.0f);
	towel->SetRotation(0.0f, -135.0f, -3.25f);
	towel->SetScale(0.125f, 0.125f, 0.125f);
	towel->SetParent(island);
	AddObject("Towel", towel);

	ObjectClass* person = new ObjectClass(ObjectClass::ModelType::Model);
	person->SetDevice(device);
	person->SetShaderManager(shaderManager);
	person->SetModel("../Engine/data/Beach man/beach_man.txt");
	person->SetTextures(L"../Engine/data/Beach man/beach_man_diffuse.dds");
	person->SetRotation(0.0f, 90.0f, 0.0f);
	person->SetScale(10.0f, 10.0f, 10.0f);
	person->SetParent(towel);
	AddObject("Person", person);

	ObjectClass* umbrella = new ObjectClass(ObjectClass::ModelType::Model);
	umbrella->SetDevice(device);
	umbrella->SetShaderManager(shaderManager);
	umbrella->SetModel("../Engine/data/Beach umbrella/beach_umbrella.txt");
	umbrella->SetTextures(L"../Engine/data/Beach umbrella/beach_umbrella_diffuse.dds");
	umbrella->SetTranslation(-25.0f, -1.5f, 60.0f);
	umbrella->SetRotation(5.0f, 0.0f, -5.0f);
	umbrella->SetScale(0.1f, 0.1f, 0.1f);
	umbrella->SetParent(island);
	AddObject("Umbrella", umbrella);

	ObjectClass* ball = new ObjectClass(ObjectClass::ModelType::SpecularModel);
	ball->SetDevice(device);
	ball->SetShaderManager(shaderManager);
	ball->SetModel("../Engine/data/Beach ball/beachball2.txt");
	ball->SetTextures(L"../Engine/data/Beach ball/diffuse5.dds");
	ball->SetTranslation(-41.25f, 0.35f, 48.75f);
	ball->SetRotation(-45.0f, 0.0f, -45.0f);
	ball->SetScale(0.025f, 0.025f, 0.025f);
	ball->SetParent(island);
	AddObject("Ball", ball);

	ObjectClass* bucket = new ObjectClass(ObjectClass::ModelType::SpecularModel);
	bucket->SetDevice(device);
	bucket->SetShaderManager(shaderManager);
	bucket->SetModel("../Engine/data/Bucket and spade/bucket.txt");
	bucket->SetTextures(L"../Engine/data/Bucket and spade/red_plastic.dds");
	bucket->SetTranslation(-50.0f, -0.75f, 65.0f);
	bucket->SetRotation(-10.0f, 130.0f, 0.0f);
	bucket->SetParent(island);
	AddObject("Bucket", bucket);

	ObjectClass* spade = new ObjectClass(ObjectClass::ModelType::SpecularModel);
	spade->SetDevice(device);
	spade->SetShaderManager(shaderManager);
	spade->SetModel("../Engine/data/Bucket and spade/spade.txt");
	spade->SetTextures(L"../Engine/data/Bucket and spade/red_plastic.dds");
	spade->SetTranslation(-45.0f, -2.4f, 70.0f);
	spade->SetRotation(0.0f, 45.0f, 10.0f);
	spade->SetScale(0.75f, 0.75f, 0.75f);
	spade->SetParent(island);
	AddObject("Spade", spade);

	ObjectClass* gull1PivotPoint = new ObjectClass(ObjectClass::ModelType::Model);
	gull1PivotPoint->SetDevice(device);
	gull1PivotPoint->SetShaderManager(shaderManager);
	gull1PivotPoint->SetModel("../Engine/data/Empty/empty.txt");
	gull1PivotPoint->SetTextures(L"../Engine/data/Empty/empty.dds");
	gull1PivotPoint->SetTranslation(0.0f, 25.0f, 0.0f);
	gull1PivotPoint->SetSpin(0.0f, 0.375f, 0.0f);
	gull1PivotPoint->SetParent(island);
	AddObject("Gull 1 Pivot Point", gull1PivotPoint);

	ObjectClass* gull1 = new ObjectClass(ObjectClass::ModelType::Model);
	gull1->SetDevice(device);
	gull1->SetShaderManager(shaderManager);
	gull1->SetModel("../Engine/data/Gull/gull.txt");
	gull1->SetTextures(L"../Engine/data/Gull/gull.dds");
	gull1->SetTranslation(175.0f, 50.0f, 0.0f);
	gull1->SetRotation(0.0f, 0.0f, 22.5f);
	gull1->SetScale(10.0f, 10.0f, 10.0f);
	gull1->SetParent(gull1PivotPoint);
	AddObject("Gull 1", gull1);

	ObjectClass* crab1 = new ObjectClass(ObjectClass::ModelType::BumpModel);
	crab1->SetDevice(device);
	crab1->SetShaderManager(shaderManager);
	crab1->SetModel("../Engine/data/Crab/crab.txt");
	crab1->SetTextures(L"../Engine/data/Crab/crab_red_diffuse.dds", L"../Engine/data/Crab/crab_red_normal.dds");
	crab1->SetTranslation(22.5f, -2.125f, -65.0f);
	crab1->SetRotation(-8.0f, -25.5f, 0.0f);
	crab1->SetScale(5.0f, 5.0f, 5.0f);
	crab1->SetParent(island);
	AddObject("Crab 1", crab1);

	ObjectClass* crab2 = new ObjectClass(ObjectClass::ModelType::BumpModel);
	crab2->SetDevice(device);
	crab2->SetShaderManager(shaderManager);
	crab2->SetModel("../Engine/data/Crab/crab.txt");
	crab2->SetTextures(L"../Engine/data/Crab/crab_purple_diffuse.dds", L"../Engine/data/Crab/crab_purple_normal.dds");
	crab2->SetTranslation(30.0f, -2.125f, -62.5f);
	crab2->SetRotation(-8.0f, 5.0f, -3.0f);
	crab2->SetScale(5.0f, 5.0f, 5.0f);
	crab2->SetParent(island);
	AddObject("Crab 2", crab2);

	ObjectClass* shell1 = new ObjectClass(ObjectClass::ModelType::Model);
	shell1->SetDevice(device);
	shell1->SetShaderManager(shaderManager);
	shell1->SetModel("../Engine/data/Conch/conch.txt");
	shell1->SetTextures(L"../Engine/data/Conch/conch_diffuse.dds");
	shell1->SetTranslation(-65.0f, -4.25f, -25.0f);
	shell1->SetRotation(10.0f, -110.0f, 0.0f);
	shell1->SetScale(10.0f, 10.0f, 10.0f);
	AddObject("Shell 1", shell1);

	ObjectClass* coconut1 = new ObjectClass(ObjectClass::ModelType::Model);
	coconut1->SetDevice(device);
	coconut1->SetShaderManager(shaderManager);
	coconut1->SetModel("../Engine/data/Coconut/coconut.txt");
	coconut1->SetTextures(L"../Engine/data/Coconut/coconut_diffuse.dds");
	coconut1->SetTranslation(65.0f, -2.0f, 25.0f);
	coconut1->SetRotation(0.0f, 0.0f, -100.0f);
	coconut1->SetScale(0.01f, 0.01f, 0.01f);
	AddObject("Coconut 1", coconut1);

	ObjectClass* boatPivotPoint = new ObjectClass(ObjectClass::ModelType::Model);
	boatPivotPoint->SetDevice(device);
	boatPivotPoint->SetShaderManager(shaderManager);
	boatPivotPoint->SetModel("../Engine/data/Empty/empty.txt");
	boatPivotPoint->SetTextures(L"../Engine/data/Empty/empty.dds");
	boatPivotPoint->SetTranslation(0.0f, -14.0f, 0.0f);
	boatPivotPoint->SetSpin(0.0f, 0.01f, 0.0f);
	boatPivotPoint->SetParent(island);
	AddObject("Boat Pivot Point", boatPivotPoint);

	ObjectClass* boat = new ObjectClass(ObjectClass::ModelType::Model);
	boat->SetDevice(device);
	boat->SetShaderManager(shaderManager);
	boat->SetModel("../Engine/data/Boat/boat.txt");
	boat->SetTextures(L"../Engine/data/Boat/boat_diffuse.dds");
	boat->SetTranslation(750.0f, 0.0f, 0.0f);
	boat->SetScale(0.1f, 0.1f, 0.1f);
	boat->SetParent(boatPivotPoint);
	AddObject("Boat", boat);

	ObjectClass* gull2PivotPoint = new ObjectClass(ObjectClass::ModelType::Model);
	gull2PivotPoint->SetDevice(device);
	gull2PivotPoint->SetShaderManager(shaderManager);
	gull2PivotPoint->SetModel("../Engine/data/Empty/empty.txt");
	gull2PivotPoint->SetTextures(L"../Engine/data/Empty/empty.dds");
	gull2PivotPoint->SetTranslation(0.0f, 25.0f, 0.0f);
	gull2PivotPoint->SetSpin(0.0f, -0.375f, 0.0f);
	gull2PivotPoint->SetParent(boat);
	AddObject("Gull 2 Pivot Point", gull2PivotPoint);

	ObjectClass* gull2 = new ObjectClass(ObjectClass::ModelType::Model);
	gull2->SetDevice(device);
	gull2->SetShaderManager(shaderManager);
	gull2->SetModel("../Engine/data/Gull/gull.txt");
	gull2->SetTextures(L"../Engine/data/Gull/gull.dds");
	gull2->SetTranslation(50.0f, 30.0f, 0.0f);
	gull2->SetRotation(0.0f, 180.0f, -22.5f);
	gull2->SetScale(10.0f, 10.0f, 10.0f);
	gull2->SetParent(gull2PivotPoint);
	AddObject("Gull 2", gull2);

	// Transparent models added last, so that existing non-transparent models can be seen through the transparent parts of these models

	ObjectClass* water = new ObjectClass(ObjectClass::ModelType::Model);
	water->SetDevice(device);
	water->SetShaderManager(shaderManager);
	water->SetModel("../Engine/data/Water/water.txt");
	water->SetTextures(L"../Engine/data/Water/water_diffuse.dds");
	water->SetTransparent(true);
	water->SetTranslation(0.0f, -15.0f, 0.0f);
	water->SetScale(100.0f, 0.0f, 100.0f);
	AddObject("Water", water);

	ObjectClass* trees1 = new ObjectClass(ObjectClass::ModelType::Model);
	trees1->SetDevice(device);
	trees1->SetShaderManager(shaderManager);
	trees1->SetModel("../Engine/data/Palm trees/palm_tree_trio.txt");
	trees1->SetTextures(L"../Engine/data/Palm trees/palm_trees_diffuse.dds");
	trees1->SetTransparent(true);
	trees1->SetTranslation(0.0f, 2.5f, 0.0f);
	trees1->SetScale(0.5f, 0.5f, 0.5f);
	trees1->SetParent(island);
	AddObject("Trees 1", trees1);

	ObjectClass* trees2 = new ObjectClass(ObjectClass::ModelType::Model);
	trees2->SetDevice(device);
	trees2->SetShaderManager(shaderManager);
	trees2->SetModel("../Engine/data/Palm trees/palm_tree_dual_bended.txt");
	trees2->SetTextures(L"../Engine/data/Palm trees/palm_trees_diffuse.dds");
	trees2->SetTransparent(true);
	trees2->SetTranslation(30.0f, 1.0f, 65.0f);
	trees2->SetRotation(0.0f, -5.0f, 0.0f);
	trees2->SetScale(0.5f, 0.5f, 0.5f);
	trees2->SetParent(island);
	AddObject("Trees 2", trees2);

	ObjectClass* trees3 = new ObjectClass(ObjectClass::ModelType::Model);
	trees3->SetDevice(device);
	trees3->SetShaderManager(shaderManager);
	trees3->SetModel("../Engine/data/Palm trees/palm_tree_dual_straight.txt");
	trees3->SetTextures(L"../Engine/data/Palm trees/palm_trees_diffuse.dds");
	trees3->SetTransparent(true);
	trees3->SetTranslation(-30.0f, -2.5f, -65.0f);
	trees3->SetRotation(0.0f, 45.0f, 0.0f);
	trees3->SetScale(0.5f, 0.5f, 0.5f);
	trees3->SetParent(island);
	AddObject("Trees 3", trees3);

	ObjectClass* trees4 = new ObjectClass(ObjectClass::ModelType::Model);
	trees4->SetDevice(device);
	trees4->SetShaderManager(shaderManager);
	trees4->SetModel("../Engine/data/Palm trees/palm_tree_single_bended.txt");
	trees4->SetTextures(L"../Engine/data/Palm trees/palm_trees_diffuse.dds");
	trees4->SetTransparent(true);
	trees4->SetTranslation(-65.0f, 0.0f, 30.0f);
	trees4->SetRotation(0.0f, 210.0f, 0.0f);
	trees4->SetScale(0.5f, 0.5f, 0.5f);
	trees4->SetParent(island);
	AddObject("Trees 4", trees4);

	ObjectClass* trees5 = new ObjectClass(ObjectClass::ModelType::Model);
	trees5->SetDevice(device);
	trees5->SetShaderManager(shaderManager);
	trees5->SetModel("../Engine/data/Palm trees/palm_tree_single_straight.txt");
	trees5->SetTextures(L"../Engine/data/Palm trees/palm_trees_diffuse.dds");
	trees5->SetTransparent(true);
	trees5->SetTranslation(65.0f, 0.0f, -30.0f);
	trees5->SetScale(0.5f, 0.5f, 0.5f);
	trees5->SetParent(island);
	AddObject("Trees 5", trees5);

	ObjectClass* foliage1 = new ObjectClass(ObjectClass::ModelType::Model);
	foliage1->SetDevice(device);
	foliage1->SetShaderManager(shaderManager);
	foliage1->SetModel("../Engine/data/Tropical foliage/tropical_foliage.txt");
	foliage1->SetTextures(L"../Engine/data/Tropical foliage/tropical_foliage_diffuse.dds");
	foliage1->SetTransparent(true);
	foliage1->SetTranslation(35.0f, 0.5f, 0.0f);
	foliage1->SetScale(5.0f, 5.0f, 5.0f);
	foliage1->SetParent(island);
	AddObject("Foliage 1", foliage1);

	ObjectClass* foliage2 = new ObjectClass(ObjectClass::ModelType::Model);
	foliage2->SetDevice(device);
	foliage2->SetShaderManager(shaderManager);
	foliage2->SetModel("../Engine/data/Tropical foliage/tropical_foliage.txt");
	foliage2->SetTextures(L"../Engine/data/Tropical foliage/tropical_foliage_diffuse.dds");
	foliage2->SetTransparent(true);
	foliage2->SetTranslation(10.0f, 0.75f, -33.0f);
	foliage2->SetRotation(0.0f, 72.0f, 0.0f);
	foliage2->SetScale(5.0f, 5.0f, 5.0f);
	foliage2->SetParent(island);
	AddObject("Foliage 2", foliage2);

	ObjectClass* foliage3 = new ObjectClass(ObjectClass::ModelType::Model);
	foliage3->SetDevice(device);
	foliage3->SetShaderManager(shaderManager);
	foliage3->SetModel("../Engine/data/Tropical foliage/tropical_foliage.txt");
	foliage3->SetTextures(L"../Engine/data/Tropical foliage/tropical_foliage_diffuse.dds");
	foliage3->SetTransparent(true);
	foliage3->SetTranslation(-28.0f, 0.25f, -20.0f);
	foliage3->SetRotation(0.0f, 144.0f, 0.0f);
	foliage3->SetScale(5.0f, 5.0f, 5.0f);
	foliage3->SetParent(island);
	AddObject("Foliage 3", foliage3);

	ObjectClass* foliage4 = new ObjectClass(ObjectClass::ModelType::Model);
	foliage4->SetDevice(device);
	foliage4->SetShaderManager(shaderManager);
	foliage4->SetModel("../Engine/data/Tropical foliage/tropical_foliage.txt");
	foliage4->SetTextures(L"../Engine/data/Tropical foliage/tropical_foliage_diffuse.dds");
	foliage4->SetTransparent(true);
	foliage4->SetTranslation(-28.0f, 0.75f, 20.0f);
	foliage4->SetRotation(0.0f, 216.0f, 0.0f);
	foliage4->SetScale(5.0f, 5.0f, 5.0f);
	foliage4->SetParent(island);
	AddObject("Foliage 4", foliage4);

	ObjectClass* foliage5 = new ObjectClass(ObjectClass::ModelType::Model);
	foliage5->SetDevice(device);
	foliage5->SetShaderManager(shaderManager);
	foliage5->SetModel("../Engine/data/Tropical foliage/tropical_foliage.txt");
	foliage5->SetTextures(L"../Engine/data/Tropical foliage/tropical_foliage_diffuse.dds");
	foliage5->SetTransparent(true);
	foliage5->SetTranslation(10.0f, 1.5f, 33.0f);
	foliage5->SetRotation(0.0f, 288.0f, 0.0f);
	foliage5->SetScale(5.0f, 5.0f, 5.0f);
	foliage5->SetParent(island);
	AddObject("Foliage 5", foliage5);
}

MyScene::~MyScene()
{
}
