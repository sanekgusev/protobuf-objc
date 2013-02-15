// Protocol Buffers for Objective C
//
// Copyright 2010 Booyah Inc.
// Copyright 2008 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "objc_enum_field.h"

#include <map>
#include <string>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/stubs/strutil.h>

#include "objc_helpers.h"

namespace google { namespace protobuf { namespace compiler { namespace objectivec {

  namespace {
    void SetEnumVariables(const FieldDescriptor* descriptor,
      map<string, string>* variables) {
        const EnumValueDescriptor* default_value;
        default_value = descriptor->default_value_enum();

        string type = ClassName(descriptor->enum_type());

        (*variables)["classname"]             = ClassName(descriptor->containing_type());
        (*variables)["name"]                  = UnderscoresToCamelCase(descriptor);
        (*variables)["capitalized_name"]      = UnderscoresToCapitalizedCamelCase(descriptor);
        (*variables)["list_name"]             = UnderscoresToCamelCase(descriptor) + "Array";
        (*variables)["number"] = SimpleItoa(descriptor->number());
        (*variables)["type"] = type;
        (*variables)["default"] = EnumValueName(default_value);
        (*variables)["tag"] = SimpleItoa(internal::WireFormat::MakeTag(descriptor));
        (*variables)["tag_size"] = SimpleItoa(
          internal::WireFormat::TagSize(descriptor->number(), descriptor->type()));
    }
  }  // namespace

  EnumFieldGenerator::EnumFieldGenerator(const FieldDescriptor* descriptor)
    : descriptor_(descriptor) {
      SetEnumVariables(descriptor, &variables_);
  }


  EnumFieldGenerator::~EnumFieldGenerator() {
  }


  void EnumFieldGenerator::GenerateHasFieldHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateFieldHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateHasPropertyHeader(io::Printer* printer) const {
    printer->Print(variables_, "- (BOOL) has$capitalized_name$;\n");
  }


  void EnumFieldGenerator::GeneratePropertyHeader(io::Printer* printer) const {
    printer->Print(variables_,
      "@property (nonatomic, readonly, getter=pb_$name$) $type$ $name$;\n");
  }


  void EnumFieldGenerator::GenerateExtensionFieldSource(io::Printer* printer) const {
    printer->Print(variables_, "BOOL _has$capitalized_name$;\n");
  }

    void EnumFieldGenerator::GenerateExtensionPropertySource(io::Printer* printer) const {
        printer->Print(variables_, "@property (nonatomic, readwrite, setter=pb_set$capitalized_name$:) $type$ $name$;\n");
    }

  void EnumFieldGenerator::GenerateMembersHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateMembersSource(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateSynthesizeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "- (BOOL) has$capitalized_name$ {\n"
      "  return !!_has$capitalized_name$;\n"
      "}\n");
    printer->Print(variables_,
       "@synthesize $name$ = _pb_$name$;\n");
  }


  void EnumFieldGenerator::GenerateDeallocSource(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateInitializationSource(io::Printer* printer) const {
    printer->Print(variables_, "self.$name$ = $default$;\n");
  }


  void EnumFieldGenerator::GenerateBuilderMembersHeader(io::Printer* printer) const {
    printer->Print(variables_,
      "- (BOOL) has$capitalized_name$;\n"
      "- ($classname$_Builder*) clear$capitalized_name$;\n"
      "@property (nonatomic, assign, getter=pb_$name$, setter=pb_set$capitalized_name$:) $type$ $name$;\n");
  }


  void EnumFieldGenerator::GenerateBuilderMembersSource(io::Printer* printer) const {
    printer->Print(variables_,
      "- (BOOL) has$capitalized_name$ {\n"
      "  return [_result has$capitalized_name$];\n"
      "}\n"
       "- ($classname$_Builder*) clear$capitalized_name$ {\n"
       "  _result->_has$capitalized_name$ = NO;\n"
       "  _result.$name$ = $default$;\n"
       "  return self;\n"
       "}\n"
      "- ($type$) pb_$name$ {\n"
      "  return _result.$name$;\n"
      "}\n"
      "- (void) pb_set$capitalized_name$:($type$) value {\n"
      "  _result->_has$capitalized_name$ = YES;\n"
      "  _result.$name$ = value;\n"
      "}\n");
  }


  void EnumFieldGenerator::GenerateMergingCodeHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateMergingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if ([other has$capitalized_name$]) {\n"
      "  self.$name$ = other.$name$;\n"
      "}\n");
  }

  void EnumFieldGenerator::GenerateBuildingCodeHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateBuildingCodeSource(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateParsingCodeHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateParsingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "int32_t value = [input readEnum];\n"
      "if ($type$IsValidValue(value)) {\n"
      "  self.$name$ = value;\n"
      "} else {\n"
      "  [unknownFields mergeVarintField:$number$ value:value];\n"
      "}\n");
  }


  void EnumFieldGenerator::GenerateSerializationCodeHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateSerializationCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if ([self has$capitalized_name$]) {\n"
      "  [output writeEnum:$number$ value:self.$name$];\n"
      "}\n");
  }


  void EnumFieldGenerator::GenerateSerializedSizeCodeHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateSerializedSizeCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if ([self has$capitalized_name$]) {\n"
      "  size += computeEnumSize($number$, self.$name$);\n"
      "}\n");
  }


  void EnumFieldGenerator::GenerateDescriptionCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if ([self has$capitalized_name$]) {\n"
      "  [output appendFormat:@\"%@%@: %d\\n\", indent, @\"$name$\", self.$name$];\n"
      "}\n");
  }


  void EnumFieldGenerator::GenerateIsEqualCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "[self has$capitalized_name$] == [otherMessage has$capitalized_name$] &&\n"
      "(![self has$capitalized_name$] || self.$name$ == otherMessage.$name$) &&");
  }


  void EnumFieldGenerator::GenerateHashCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if ([self has$capitalized_name$]) {\n"
      "  hashCode = hashCode * 31 + self.$name$;\n"
      "}\n");
  }


  string EnumFieldGenerator::GetBoxedType() const {
    return ClassName(descriptor_->enum_type());
  }


  RepeatedEnumFieldGenerator::RepeatedEnumFieldGenerator(const FieldDescriptor* descriptor)
    : descriptor_(descriptor) {
      SetEnumVariables(descriptor, &variables_);
  }


  RepeatedEnumFieldGenerator::~RepeatedEnumFieldGenerator() {
  }


  void RepeatedEnumFieldGenerator::GenerateHasFieldHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateFieldHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateHasPropertyHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GeneratePropertyHeader(io::Printer* printer) const {
    printer->Print(variables_, "@property (nonatomic, readonly, retain, getter=pb_$name$) PBArray * $name$;\n");
  }


  void RepeatedEnumFieldGenerator::GenerateExtensionFieldSource(io::Printer* printer) const {
    printer->Print(variables_,
      "PBAppendableArray *_pb_$name$;\n");
      if (descriptor_->options().packed()) {
          printer->Print(variables_,
                         "int32_t _$name$MemorizedSerializedSize;\n");
      }
  }

    void RepeatedEnumFieldGenerator::GenerateExtensionPropertySource(io::Printer* printer) const {
        printer->Print(variables_, "@property (nonatomic, readwrite, retain, setter=pb_set$capitalized_name$:) PBArray *$name$;\n");
    }

  void RepeatedEnumFieldGenerator::GenerateSynthesizeSource(io::Printer* printer) const {
    printer->Print(variables_, "@synthesize $name$ = _pb_$name$;\n");
  }

  void RepeatedEnumFieldGenerator::GenerateDeallocSource(io::Printer* printer) const {
    printer->Print(variables_,
      "[_pb_$name$ release];\n");
  }


  void RepeatedEnumFieldGenerator::GenerateInitializationSource(io::Printer* printer) const {
      printer->Print(variables_, "_pb_$name$ = [[PBAppendableArray alloc] init];");
  }


  void RepeatedEnumFieldGenerator::GenerateMembersHeader(io::Printer* printer) const {
    printer->Print(variables_,
      "- ($type$)$name$AtIndex:(NSUInteger)index;\n");
  }

  void RepeatedEnumFieldGenerator::GenerateBuilderMembersHeader(io::Printer* printer) const {
    printer->Print(variables_,
      "- (PBAppendableArray *)pb_$name$;\n"
      "- ($type$)$name$AtIndex:(NSUInteger)index;\n"
      "- ($classname$_Builder *)add$capitalized_name$:($type$)value;\n"
      "- ($classname$_Builder *)set$capitalized_name$Array:(NSArray *)array;\n"
      "- ($classname$_Builder *)set$capitalized_name$Values:(const $type$ *)values count:(NSUInteger)count;\n"
      "- ($classname$_Builder *)clear$capitalized_name$;\n");
  }


  void RepeatedEnumFieldGenerator::GenerateMergingCodeHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateBuildingCodeHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateParsingCodeHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateSerializationCodeHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateSerializedSizeCodeHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateMembersSource(io::Printer* printer) const {
    printer->Print(variables_,
      "- ($type$)$name$AtIndex:(NSUInteger)index {\n"
      "  return [_pb_$name$ int32AtIndex:index];\n"
      "}\n");
  }

  void RepeatedEnumFieldGenerator::GenerateBuilderMembersSource(io::Printer* printer) const {
    printer->Print(variables_,
      "- (PBAppendableArray *)pb_$name$ {\n"
      "  return _result->_pb_$name$;\n"
      "}\n"
      "- ($type$)$name$AtIndex:(NSUInteger)index {\n"
      "  return [_result $name$AtIndex:index];\n"
      "}\n"
      "- ($classname$_Builder *)add$capitalized_name$:($type$)value {\n"
      "  if (_result.$name$ == nil) {\n"
      "    _result.$name$ = [PBAppendableArray arrayWithValueType:PBArrayValueTypeInt32];\n"
      "  }\n"
      "  [_result->_pb_$name$ addInt32:value];\n"
      "  return self;\n"
      "}\n"
      "- ($classname$_Builder *)set$capitalized_name$Array:(NSArray *)array {\n"
      "  _result.$name$ = [PBAppendableArray arrayWithArray:array valueType:PBArrayValueTypeInt32];\n"
      "  return self;\n"
      "}\n"
      "- ($classname$_Builder *)set$capitalized_name$Values:(const $type$ *)values count:(NSUInteger)count {\n"
      "  _result.$name$ = [PBAppendableArray arrayWithValues:values count:count valueType:PBArrayValueTypeInt32];\n"
      "  return self;\n"
      "}\n"
      "- ($classname$_Builder *)clear$capitalized_name$ {\n"
      "  _result.$name$ = nil;\n"
      "  return self;\n"
      "}\n");
  }

  void RepeatedEnumFieldGenerator::GenerateMergingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if ([other.$name$ count] > 0) {\n"
      "  if (_result.$name$ == nil) {\n"
      "    _result.$name$ = [[other.$name$ copyWithZone:[other.$name$ zone]] autorelease];\n"
      "  } else {\n"
      "    [_result->_pb_$name$ appendArray:other.$name$];\n"
      "  }\n"
      "}\n");
  }

  void RepeatedEnumFieldGenerator::GenerateBuildingCodeSource(io::Printer* printer) const {
  }

  void RepeatedEnumFieldGenerator::GenerateParsingCodeSource(io::Printer* printer) const {
    // If packed, set up the while loop
    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "int32_t length = [input readRawVarint32];\n"
        "int32_t oldLimit = [input pushLimit:length];\n"
        "while (input.bytesUntilLimit > 0) {\n");
      printer->Indent();
    }

    printer->Print(variables_,
      "int32_t value = [input readEnum];\n"
      "if ($type$IsValidValue(value)) {\n"
      "  [self add$capitalized_name$:value];\n"
      "} else {\n"
      "  [unknownFields mergeVarintField:$number$ value:value];\n"
      "}\n");

    if (descriptor_->options().packed()) {
      printer->Outdent();
      printer->Print(variables_,
        "}\n"
        "[input popLimit:oldLimit];\n");
    }
  }

  void RepeatedEnumFieldGenerator::GenerateSerializationCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
        "const NSUInteger $name$Count = [self.$name$ count];\n"
        "const $type$ *$name$Values = (const $type$ *)self.$name$.data;\n");

    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "if ($name$Count > 0) {\n"
        "  [output writeRawVarint32:$tag$];\n"
        "  [output writeRawVarint32:_$name$MemorizedSerializedSize];\n"
        "}\n"
        "for (NSUInteger i = 0; i < $name$Count; ++i) {\n"
        "  [output writeEnumNoTag:$name$Values[i]];\n"
        "}\n");
    } else {
      printer->Print(variables_,
        "for (NSUInteger i = 0; i < $name$Count; ++i) {\n"
        "  [output writeEnum:$number$ value:$name$Values[i]];\n"
        "}\n");
    }
  }


  void RepeatedEnumFieldGenerator::GenerateSerializedSizeCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "{\n"
      "  int32_t dataSize = 0;\n"
      "  const NSUInteger count = [self.$name$ count];\n");
    printer->Indent();

    printer->Print(variables_,
      "const $type$ *values = (const $type$ *)self.$name$.data;\n"
      "for (NSUInteger i = 0; i < count; ++i) {\n"
      "  dataSize += computeEnumSizeNoTag(values[i]);\n"
      "}\n");

    printer->Print(
      "size += dataSize;\n");

    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "if (count > 0) {\n"
        "  size += $tag_size$;\n"
        "  size += computeRawVarint32Size(dataSize);\n"
        "}\n");
    } else {
      printer->Print(variables_,
        "size += $tag_size$ * count;\n");
    }

    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "_$name$MemorizedSerializedSize = dataSize;\n");
    }

    printer->Outdent();
    printer->Print("}\n");
  }


  void RepeatedEnumFieldGenerator::GenerateDescriptionCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "for (NSNumber* element in self.$name$) {\n"
      "  [output appendFormat:@\"%@%@: %d\\n\", indent, @\"$name$\", [element intValue]];\n"
      "}\n");
  }


  void RepeatedEnumFieldGenerator::GenerateIsEqualCodeSource(io::Printer* printer) const {
    printer->Print(variables_, "[self.$name$ isEqualToArray:otherMessage.$name$] &&");
  }


  void RepeatedEnumFieldGenerator::GenerateHashCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "for (NSNumber* element in self.$name$) {\n"
      "  hashCode = hashCode * 31 + [element intValue];\n"
      "}\n");
  }
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
