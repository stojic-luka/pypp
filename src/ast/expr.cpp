#include "expr.h"

#include <ostream>

#include "../exprs/assignmentExpr.h"
#include "../exprs/binaryExpr.h"
#include "../exprs/callExpr.h"
#include "../exprs/memberExpr.h"
#include "../exprs/ifExpr.h"
#include "../exprs/forExpr.h"
#include "../exprs/whileExpr.h"
#include "identifier.h"
#include "numericLiteral.h"
#include "charactersLiteral.h"
#include "property.h"
#include "objectLiteral.h"

void Expr::print(std::ostream& os, int indentation) const {
	switch (this->getKind()) {
	case NodeType::AssignmentExpr: {
		static_cast<const AssignmentExpr*>(this)->print(os, indentation);
		break;
	}
	case NodeType::BinaryExpr: {
		static_cast<const BinaryExpr*>(this)->print(os, indentation);
		break;
	}
	case NodeType::CallExpr: {
		static_cast<const CallExpr*>(this)->print(os, indentation);
		break;
	}
	case NodeType::MemberExpr: {
		static_cast<const MemberExpr*>(this)->print(os, indentation);
		break;
	}
	case NodeType::IfExpr: {
		static_cast<const IfExpr*>(this)->print(os, indentation);
		break;
	}
	case NodeType::ForExpr: {
		static_cast<const ForExpr*>(this)->print(os, indentation);
		break;
	}
	case NodeType::WhileExpr: {
		static_cast<const WhileExpr*>(this)->print(os, indentation);
		break;
	}
	case NodeType::Identifier: {
		static_cast<const Identifier*>(this)->print(os, indentation);
		break;
	}
	case NodeType::NumericLiteral: {
		static_cast<const NumericLiteral*>(this)->print(os, indentation);
		break;
	}
	case NodeType::CharactersLiteral: {
		static_cast<const CharactersLiteral*>(this)->print(os, indentation);
		break;
	}
	case NodeType::Property: {
		static_cast<const Property*>(this)->print(os, indentation);
		break;
	}
	case NodeType::ObjectLiteral: {
		static_cast<const ObjectLiteral*>(this)->print(os, indentation);
		break;
	}
	}
	os << ",\n";
}