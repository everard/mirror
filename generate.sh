#!/bin/sh
# Copyright Nezametdinov E. Ildus 2023.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt)
#
STYLE="{Language: Cpp,\
AccessModifierOffset: -4,\
ConstructorInitializerIndentWidth: 4,\
AlignEscapedNewlinesLeft: true,\
AlignTrailingComments: true,\
AllowAllParametersOfDeclarationOnNextLine: true,\
AllowShortBlocksOnASingleLine: false,\
AllowShortCaseLabelsOnASingleLine: false,\
AllowShortIfStatementsOnASingleLine: false,\
AllowShortLoopsOnASingleLine: false,\
AllowShortFunctionsOnASingleLine: false,\
AlwaysBreakTemplateDeclarations: true,\
AlwaysBreakBeforeMultilineStrings: true,\
AlwaysBreakAfterReturnType: All,\
BreakBeforeBinaryOperators: false,\
BreakBeforeBraces: Attach,\
BreakBeforeTernaryOperators: true,\
BreakBeforeConceptDeclarations: Always,\
BreakConstructorInitializersBeforeComma: true,\
BinPackParameters: true,\
ColumnLimit: 80,\
ConstructorInitializerAllOnOneLineOrOnePerLine: true,\
DerivePointerAlignment: false,\
ExperimentalAutoDetectBinPacking: false,\
FixNamespaceComments: true,\
IndentCaseLabels: true,\
IndentRequiresClause: true,\
IndentWrappedFunctionNames: false,\
IndentFunctionDeclarationAfterType: false,\
MaxEmptyLinesToKeep: 1,\
KeepEmptyLinesAtTheStartOfBlocks: false,\
NamespaceIndentation: None,\
ObjCSpaceAfterProperty: false,\
ObjCSpaceBeforeProtocolList: false,\
PenaltyBreakBeforeFirstCallParameter: 0,\
PenaltyBreakComment: 300,\
PenaltyBreakString: 1000,\
PenaltyBreakFirstLessLess: 120,\
PenaltyExcessCharacter: 1000000,\
PenaltyReturnTypeOnItsOwnLine: 200,\
PointerAlignment: Left,\
QualifierAlignment: Custom,\
QualifierOrder: ['static', 'constexpr', 'inline', 'restrict', 'type', 'const', 'volatile' ],\
RequiresClausePosition: WithFollowing,\
SpacesBeforeTrailingComments: 1,\
Cpp11BracedListStyle: true,\
Standard: 'c++20',\
IndentWidth: 4,\
TabWidth: 4,\
UseTab: Never,\
SpacesInParentheses: false,\
SpacesInAngles: false,\
SpaceInEmptyParentheses: false,\
SpacesInCStyleCastParentheses: false,\
SpacesInContainerLiterals: true,\
SpaceBeforeAssignmentOperators: true,\
ContinuationIndentWidth: 4,\
CommentPragmas: '^ IWYU pragma:',\
ForEachMacros: [ foreach, Q_FOREACH, BOOST_FOREACH ],\
SpaceBeforeParens: Never,\
SortIncludes: false,\
DisableFormat: false}"

python3 meta.py meta/mirror.ccm src/mirror.ccm $1
clang-format --style="${STYLE}" -i src/mirror.ccm
