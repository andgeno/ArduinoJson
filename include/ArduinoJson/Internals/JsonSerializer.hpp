// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "JsonWriter.hpp"

namespace ArduinoJson {

class JsonArray;
class JsonArraySubscript;
class JsonObject;
template <typename TKey>
class JsonObjectSubscript;
class JsonVariant;

namespace Internals {

class JsonSerializer {
  JsonWriter &_writer;

 public:
  explicit JsonSerializer(JsonWriter &writer) : _writer(writer) {}

  void serialize(const JsonArray &);
  void serialize(const JsonArraySubscript &);
  void serialize(const JsonObject &);
  template <typename TKey>
  void serialize(const JsonObjectSubscript<TKey> &);
  void serialize(const JsonVariant &);
};
}
}
