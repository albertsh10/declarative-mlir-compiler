#pragma once

#include "SpecAttrDetail.h"
#include "SpecTypes.h"

#include <mlir/IR/StandardTypes.h>

namespace dmc {

namespace detail {
struct ConstantAttrStorage;
struct AttrListStorage;
struct OneTypeAttrStorage;
struct DefaultAttrStorage;
} // end namespace detail

class AnyAttr : public SimpleAttr<AnyAttr, SpecAttrs::Any> {
public:
  using Base::Base;
  inline mlir::LogicalResult verify(Attribute) { return mlir::success(); }
};

class BoolAttr : public SimpleAttr<BoolAttr, SpecAttrs::Bool> {
public:
  using Base::Base;
  inline mlir::LogicalResult verify(Attribute attr) {
    return mlir::success(attr.isa<mlir::BoolAttr>());
  }
};

class IndexAttr : public SimpleAttr<IndexAttr, SpecAttrs::Index> {
public:
  using Base::Base;
  inline mlir::LogicalResult verify(Attribute attr) {
    return mlir::success(attr.isa<mlir::IntegerAttr>() &&
        attr.cast<mlir::IntegerAttr>().getType().isa<mlir::IndexType>());
  }
};

class APIntAttr : public SimpleAttr<APIntAttr, SpecAttrs::APInt> {
public:
  using Base::Base;
  inline mlir::LogicalResult verify(Attribute attr) {
    return mlir::success(attr.isa<mlir::IntegerAttr>());
  }
};

class AnyIAttr : public TypedAttrBase<AnyIAttr,
                 SpecAttrs::AnyI, mlir::IntegerAttr, AnyIType> {
public:
  using Base::Base;
};

class IAttr : public TypedAttrBase<IAttr,
              SpecAttrs::I, mlir::IntegerAttr, IType> {
public:
  using Base::Base;
};

class SIAttr : public TypedAttrBase<SIAttr,
               SpecAttrs::SI, mlir::IntegerAttr, SIType> {
public:
  using Base::Base;
};

class UIAttr : public TypedAttrBase<UIAttr,
               SpecAttrs::UI, mlir::IntegerAttr, UIType> {
public:
  using Base::Base;
};

class FAttr : public TypedAttrBase<FAttr,
              SpecAttrs::F, mlir::FloatAttr, FType> {
public:
  using Base::Base;
};

class StringAttr : public SimpleAttr<StringAttr, SpecAttrs::String> {
public:
  using Base::Base;
  inline mlir::LogicalResult verify(Attribute attr) {
    return mlir::success(attr.isa<mlir::StringAttr>());
  }
};

class TypeAttr : public SimpleAttr<TypeAttr, SpecAttrs::Type> {
public:
  using Base::Base;
  inline mlir::LogicalResult verify(Attribute attr) {
    return mlir::success(attr.isa<mlir::TypeAttr>());
  }
};

class UnitAttr : public SimpleAttr<UnitAttr, SpecAttrs::Unit> {
public:
  using Base::Base;
  inline mlir::LogicalResult verify(Attribute attr) {
    return mlir::success(attr.isa<mlir::UnitAttr>());
  }
};

class DictionaryAttr : public SimpleAttr<DictionaryAttr,
                                         SpecAttrs::Dictionary> {
public:
  using Base::Base;
  inline mlir::LogicalResult verify(Attribute attr) {
    return mlir::success(attr.isa<mlir::DictionaryAttr>());
  }
};

class ElementsAttr : public SimpleAttr<ElementsAttr,
                                       SpecAttrs::Elements> {
public:
  using Base::Base;
  inline mlir::LogicalResult verify(Attribute attr) {
    return mlir::success(attr.isa<mlir::ElementsAttr>());
  }
};

class ArrayAttr : public SimpleAttr<ArrayAttr, SpecAttrs::Array> {
public:
  using Base::Base;
  inline mlir::LogicalResult verify(Attribute attr) {
    return mlir::success(attr.isa<mlir::ArrayAttr>());
  }
};

class SymbolRefAttr : public SimpleAttr<SymbolRefAttr, SpecAttrs::SymbolRef> {
public:
  using Base::Base;
  inline mlir::LogicalResult verify(Attribute attr) {
    return mlir::success(attr.isa<mlir::SymbolRefAttr>());
  }
};

class FlatSymbolRefAttr : public SimpleAttr<FlatSymbolRefAttr,
                                            SpecAttrs::FlatSymbolRef> {
public:
  using Base::Base;
  inline mlir::LogicalResult verify(Attribute attr) {
    return mlir::success(attr.isa<mlir::FlatSymbolRefAttr>());
  }
};

class ConstantAttr : public SpecAttr<ConstantAttr, SpecAttrs::Constant,
                                     detail::ConstantAttrStorage> {
public:
  using Base::Base;

  static ConstantAttr get(Attribute attr);
  static ConstantAttr getChecked(mlir::Location loc, Attribute attr);
  static mlir::LogicalResult verifyConstructionInvariants(
      mlir::Location loc, Attribute attr);
  mlir::LogicalResult verify(Attribute attr);

  static Attribute parse(mlir::DialectAsmParser &parser);
  void print(mlir::DialectAsmPrinter &printer);
};

class AnyOfAttr : public SpecAttr<AnyOfAttr, SpecAttrs::AnyOf,
                                  detail::AttrListStorage> {
public:
  using Base::Base;

  static AnyOfAttr get(llvm::ArrayRef<Attribute> attrs);
  static AnyOfAttr getChecked(mlir::Location loc,
                                 llvm::ArrayRef<Attribute> attrs);
  static mlir::LogicalResult verifyConstructionInvariants(
      mlir::Location loc, llvm::ArrayRef<Attribute> attrs);
  mlir::LogicalResult verify(Attribute attr);
};

class AllOfAttr : public SpecAttr<AllOfAttr, SpecAttrs::AllOf,
                                  detail::AttrListStorage> {
public:
  using Base::Base;

  static AllOfAttr get(llvm::ArrayRef<Attribute> attrs);
  static AllOfAttr getChecked(mlir::Location loc,
                                 llvm::ArrayRef<Attribute> attrs);
  static mlir::LogicalResult verifyConstructionInvariants(
      mlir::Location loc, llvm::ArrayRef<Attribute> attrs);
  mlir::LogicalResult verify(Attribute attr);
};

class OfTypeAttr : public SpecAttr<OfTypeAttr, SpecAttrs::OfType,
                                  detail::OneTypeAttrStorage> {
public:
  using Base::Base;

  static OfTypeAttr get(mlir::Type ty, mlir::MLIRContext *ctx);
  static OfTypeAttr getChecked(mlir::Location loc, mlir::Type ty);
  static mlir::LogicalResult verifyConstructionInvariants(
      mlir::Location loc, mlir::Type ty);
  mlir::LogicalResult verify(Attribute attr);

  static Attribute parse(mlir::DialectAsmParser &parser);
  void print(mlir::DialectAsmPrinter &printer);
};

/// An optional attribute. The generated Attribute constraint will not check
/// for the Attribute's presence, but will apply the constraint if present.
class OptionalAttr : public SpecAttr<OptionalAttr, SpecAttrs::Optional,
                                     detail::ConstantAttrStorage> {
public:
  using Base::Base;

  static OptionalAttr get(Attribute baseAttr);
  static OptionalAttr getChecked(mlir::Location loc, Attribute baseAttr);
  static mlir::LogicalResult verifyConstructionInvariants(
      mlir::Location loc, Attribute baseAttr);
  mlir::LogicalResult verify(Attribute attr);

  static Attribute parse(mlir::DialectAsmParser &parser);
  void print(mlir::DialectAsmPrinter &printer);
};

/// A default-valued attribute. During Op post-construction, if this attribute
/// was not provided, the default value will be used.
class DefaultAttr : public SpecAttr<DefaultAttr, SpecAttrs::Default,
                                    detail::DefaultAttrStorage> {
public:
  using Base::Base;

  static DefaultAttr get(Attribute baseAttr, Attribute defaultAttr);
  static DefaultAttr getChecked(mlir::Location loc,
      Attribute baseAttr, Attribute defaultAttr);
  static mlir::LogicalResult verifyConstructionInvariants(
      mlir::Location loc, Attribute baseAttr, Attribute defaultAttr);
  mlir::LogicalResult verify(Attribute attr);

  static Attribute parse(mlir::DialectAsmParser &parser);
  void print(mlir::DialectAsmPrinter &printer);

  /// Get the default value.
  Attribute getDefaultValue();
};

/// TODO typed elements attributes: int, float, ranked, string
/// TODO typed array attributes: int, float, string, type, symbolRef
/// TODO struct attributes, enum attributes?

} // end namespace dmc