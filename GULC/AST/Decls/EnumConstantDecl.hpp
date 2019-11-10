// Copyright (C) 2019 Michael Brandon Huddle
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef GULC_ENUMCONSTANTDECL_HPP
#define GULC_ENUMCONSTANTDECL_HPP

#include <AST/Decl.hpp>
#include <AST/Expr.hpp>

namespace gulc {
    class EnumConstantDecl : public Decl {
    public:
        static bool classof(const Decl *decl) { return decl->getDeclKind() == Kind::EnumConstant; }

        EnumConstantDecl(std::string name, std::string sourceFile, TextPosition startPosition, TextPosition endPosition,
                         Expr* constantValue)
                : Decl(Kind::EnumConstant, std::move(name), std::move(sourceFile), startPosition, endPosition,
                       Visibility::Unspecified),
                  constantValue(constantValue) {}

        Expr* constantValue;

        bool hasConstantValue() const { return constantValue != nullptr; }

        Decl* deepCopy() const override {
            auto result = new EnumConstantDecl(name(), sourceFile(),
                                               startPosition(), endPosition(),
                                               constantValue->deepCopy());
            result->parentNamespace = parentNamespace;
            result->parentStruct = parentStruct;
            return result;
        }

        ~EnumConstantDecl() override {
            delete constantValue;
        }

    };
}

#endif //GULC_ENUMCONSTANTDECL_HPP
