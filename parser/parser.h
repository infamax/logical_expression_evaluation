#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <tokenizer.h>
#include <syntax_analyzer.h>
#include <node.h>

std::shared_ptr<Node> Parse(std::vector<Token>& tokens, const std::unordered_map<std::string, int>& vars);