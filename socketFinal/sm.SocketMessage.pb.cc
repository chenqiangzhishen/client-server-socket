// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sm.SocketMessage.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "sm.SocketMessage.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace sm {

namespace {

const ::google::protobuf::Descriptor* SocketMessage_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SocketMessage_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_sm_2eSocketMessage_2eproto() {
  protobuf_AddDesc_sm_2eSocketMessage_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "sm.SocketMessage.proto");
  GOOGLE_CHECK(file != NULL);
  SocketMessage_descriptor_ = file->message_type(0);
  static const int SocketMessage_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SocketMessage, received_key_id_plus_1_),
  };
  SocketMessage_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SocketMessage_descriptor_,
      SocketMessage::default_instance_,
      SocketMessage_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SocketMessage, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SocketMessage, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SocketMessage));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_sm_2eSocketMessage_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SocketMessage_descriptor_, &SocketMessage::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_sm_2eSocketMessage_2eproto() {
  delete SocketMessage::default_instance_;
  delete SocketMessage_reflection_;
}

void protobuf_AddDesc_sm_2eSocketMessage_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\026sm.SocketMessage.proto\022\002sm\"/\n\rSocketMe"
    "ssage\022\036\n\026received_key_id_plus_1\030\001 \002(\005", 77);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "sm.SocketMessage.proto", &protobuf_RegisterTypes);
  SocketMessage::default_instance_ = new SocketMessage();
  SocketMessage::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_sm_2eSocketMessage_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_sm_2eSocketMessage_2eproto {
  StaticDescriptorInitializer_sm_2eSocketMessage_2eproto() {
    protobuf_AddDesc_sm_2eSocketMessage_2eproto();
  }
} static_descriptor_initializer_sm_2eSocketMessage_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int SocketMessage::kReceivedKeyIdPlus1FieldNumber;
#endif  // !_MSC_VER

SocketMessage::SocketMessage()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void SocketMessage::InitAsDefaultInstance() {
}

SocketMessage::SocketMessage(const SocketMessage& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void SocketMessage::SharedCtor() {
  _cached_size_ = 0;
  received_key_id_plus_1_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SocketMessage::~SocketMessage() {
  SharedDtor();
}

void SocketMessage::SharedDtor() {
  if (this != default_instance_) {
  }
}

void SocketMessage::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SocketMessage::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SocketMessage_descriptor_;
}

const SocketMessage& SocketMessage::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_sm_2eSocketMessage_2eproto();
  return *default_instance_;
}

SocketMessage* SocketMessage::default_instance_ = NULL;

SocketMessage* SocketMessage::New() const {
  return new SocketMessage;
}

void SocketMessage::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    received_key_id_plus_1_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool SocketMessage::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 received_key_id_plus_1 = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &received_key_id_plus_1_)));
          set_has_received_key_id_plus_1();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void SocketMessage::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 received_key_id_plus_1 = 1;
  if (has_received_key_id_plus_1()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->received_key_id_plus_1(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* SocketMessage::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 received_key_id_plus_1 = 1;
  if (has_received_key_id_plus_1()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->received_key_id_plus_1(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int SocketMessage::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 received_key_id_plus_1 = 1;
    if (has_received_key_id_plus_1()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->received_key_id_plus_1());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void SocketMessage::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SocketMessage* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SocketMessage*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SocketMessage::MergeFrom(const SocketMessage& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_received_key_id_plus_1()) {
      set_received_key_id_plus_1(from.received_key_id_plus_1());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SocketMessage::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SocketMessage::CopyFrom(const SocketMessage& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SocketMessage::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void SocketMessage::Swap(SocketMessage* other) {
  if (other != this) {
    std::swap(received_key_id_plus_1_, other->received_key_id_plus_1_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SocketMessage::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SocketMessage_descriptor_;
  metadata.reflection = SocketMessage_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace sm

// @@protoc_insertion_point(global_scope)
