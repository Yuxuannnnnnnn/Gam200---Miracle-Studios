#pragma once



class ResourceManager
{
	//	start with the basic resources manager, single class that ctrl all loading freeing of HDD stuff
	//	not absolutely necessary to load ALL resources at start.
	//	GOFac should have a resources manager, which based on which level im loading, which assets I should load
	//	level file, at the top, should have a list of all assets to load, then loadand then continue the instancing of the level
	//	can worry about this after segment
	//	when saving a level in editor, it should save the assets necessary, and then save the instancing of the objects
	//	will have func() to load things like texture, obj prefabbing, audio, etc

	std::vector<std::string*> VecFilePaths; // for future use for dynamic file path getting	
};

