/**
 * Edit this file to provide answers as to where each of the indicated functions
 * sits in the Venn diagram provided in the problem set handout. You will likely
 * want to read the comments on the Position type for more information about this.
 *
 * This header file does not contain any local test cases. You'll need to submit
 * it to the autograder on GradeScope to get feedback on it.
 */

#ifndef FunctionsVennDiagram_Included
#define FunctionsVennDiagram_Included

/**
 * Type: Position
 *
 * An enumerated type representing a position in the Venn diagram.
 */
enum class Position {
    NotAFunction,           // The object isn't even a function.
    JustAFunction,          // It's a function, but it's not injective or surjective.
    InjectionNotSurjection, // It's an injection, but not a surjection.
    SurjectionNotInjection, // It's a surjection, but not an injection.
    Bijection,              // It's a bijection.
    TODO_AnswerMe           // Default value given when you haven't yet provided an answer.
};

/**
 * Location of (1) in the Venn diagram. It's a function, but it's not injective or surjective
 * (do you see why?)
 *
 * Notice that the answer is provided by writing Position::JustAFunction. This is the syntax
 * you'll use to select which option you think applies.
 */
const Position q1 = Position::JustAFunction;

/**
 * Location of (2) in the Venn diagram. It's not a function (do you see why?)
 *
 * Again, notice the use of the syntax Position::NotAFunction to indicate what the answer is.
 */
const Position q2 = Position::NotAFunction;

/* You need to edit the answers below. */

const Position q3  = Position::TODO_AnswerMe;
const Position q4  = Position::TODO_AnswerMe;
const Position q5  = Position::TODO_AnswerMe;
const Position q6  = Position::TODO_AnswerMe;
const Position q7  = Position::TODO_AnswerMe;
const Position q8  = Position::TODO_AnswerMe;
const Position q9  = Position::TODO_AnswerMe;
const Position q10 = Position::TODO_AnswerMe;
const Position q11 = Position::TODO_AnswerMe;
const Position q12 = Position::TODO_AnswerMe;
const Position q13 = Position::TODO_AnswerMe;
const Position q14 = Position::TODO_AnswerMe;
const Position q15 = Position::TODO_AnswerMe;
const Position q16 = Position::TODO_AnswerMe;


#endif
