// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "../JsonArray.hpp"
#include "../JsonArraySubscript.hpp"
#include "../JsonObject.hpp"
#include "../JsonObjectSubscript.hpp"
#include "../JsonVariant.hpp"
#include "JsonSerializer.hpp"

inline void ArduinoJson::Internals::JsonSerializer::serialize(
    const JsonArray &array) {
  _writer.beginArray();

  JsonArray::const_iterator it = array.begin();
  while (it != array.end()) {
    serialize(*it);

    ++it;
    if (it == array.end()) break;

    _writer.writeComma();
  }

  _writer.endArray();
}

inline void ArduinoJson::Internals::JsonSerializer::serialize(
    const JsonArraySubscript &arraySubscript) {
  serialize(arraySubscript.as<JsonVariant>());
}

// Serialize the object to the specified JsonWriter
inline void ArduinoJson::Internals::JsonSerializer::serialize(
    const JsonObject &object) {
  _writer.beginObject();

  JsonObject::const_iterator it = object.begin();
  while (it != object.end()) {
    _writer.writeString(it->key);
    _writer.writeColon();
    serialize(it->value);

    ++it;
    if (it == object.end()) break;

    _writer.writeComma();
  }

  _writer.endObject();
}

template <typename TKey>
inline void ArduinoJson::Internals::JsonSerializer::serialize(
    const JsonObjectSubscript<TKey> &objectSubscript) {
  serialize(objectSubscript.template as<JsonVariant>());
}

inline void ArduinoJson::Internals::JsonSerializer::serialize(
    const JsonVariant &variant) {
  switch (variant._type) {
    case JSON_UNDEFINED:
      return;

    case JSON_ARRAY:
      serialize(*variant._content.asArray);
      return;

    case JSON_OBJECT:
      serialize(*variant._content.asObject);
      return;

    case JSON_STRING:
      _writer.writeString(variant._content.asString);
      return;

    case JSON_UNPARSED:
      _writer.writeRaw(variant._content.asString);
      return;

    case JSON_NEGATIVE_INTEGER:
      _writer.writeRaw('-');
    case JSON_POSITIVE_INTEGER:
      _writer.writeInteger(variant._content.asInteger);
      return;

    case JSON_BOOLEAN:
      _writer.writeBoolean(variant._content.asInteger != 0);
      return;

    default:
      uint8_t decimals =
          static_cast<uint8_t>(variant._type - JSON_FLOAT_0_DECIMALS);
      _writer.writeFloat(variant._content.asFloat, decimals);
  }
}
