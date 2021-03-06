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

#ifndef GULC_INDEXERCALLEXPR_HPP
#define GULC_INDEXERCALLEXPR_HPP

#include <AST/Expr.hpp>
#include <vector>

namespace gulc {
    class IndexerCallExpr : public Expr {
    public:
        static bool classof(const Expr *expr) { return expr->getExprKind() == Kind::IndexerCall; }

        IndexerCallExpr(TextPosition startPosition, TextPosition endPosition,
                        Expr* indexerReference, std::vector<Expr*> arguments)
                : Expr(Kind::IndexerCall, startPosition, endPosition),
                  indexerReference(indexerReference), arguments(std::move(arguments)) {}

        Expr* indexerReference;
        std::vector<Expr*> arguments;
        bool hasArguments() const { return !arguments.empty(); }

        Expr* deepCopy() const override {
            std::vector<Expr*> copiedArguments;

            for (Expr* argument : arguments) {
                copiedArguments.push_back(argument->deepCopy());
            }

            auto result = new IndexerCallExpr(startPosition(), endPosition(),
                                              indexerReference->deepCopy(), std::move(copiedArguments));
            if (resultType) {
                result->resultType = resultType->deepCopy();
            }
            result->isUnreachable = isUnreachable;
            return result;
        }

        ~IndexerCallExpr() override {
            delete indexerReference;

            for (Expr* argument : arguments) {
                delete argument;
            }
        }

    };
}

#endif //GULC_INDEXERCALLEXPR_HPP
