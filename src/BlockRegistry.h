#pragma once
#include "BlockType.h"
#include <unordered_map>
#include <vector>

class BlockRegistry {
public:
	static BlockRegistry& getInstance() {
		static BlockRegistry instance;
		return instance;
	};

	void registerBlock(const BlockType& block) {
		blockTypes[block.id] = block;
		order.push_back(block.id);
	}

	const BlockType& get(int id) const { return blockTypes.at(id); }

	const std::vector<int>& allIDs() const { return order; }

private:
	std::unordered_map<int, BlockType> blockTypes;
	std::vector<int> order;
};