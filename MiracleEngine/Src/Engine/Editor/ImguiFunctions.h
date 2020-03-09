#pragma once



struct ComboFilterState
{
	int  activeIdx;         // Index of currently 'active' item by use of up/down keys
	bool selectionChanged;  // Flag to help focus the correct item when selecting active item
};


class ImGuiFunctions
{
public:

	bool ComboFilter__DrawPopup(std::string comboName, ComboFilterState& state, int START, /*const char** ENTRIES*/   std::vector<const char*> ENTRIES, int ENTRY_COUNT, std::string& _fileName, bool* open, int i = 0);

	bool ComboFilter(const char* id, char* buffer, int bufferlen, /*const char** hints*/ std::vector<const char*> hints, int num_hints, ComboFilterState& s, std::string& _filename, bool* open, int i = 0);

};