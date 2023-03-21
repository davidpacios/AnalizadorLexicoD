#ifndef CM1_SYMBOLSTABLE_H
#define CM1_SYMBOLSTABLE_H

#include "hashTableRelocation.h"

/********** TOKENS **********/
/********** KEYWORDS **********/
#define TOTAL_KEYWORDS  102
#define ABSTRACT 400
#define ALIAS 401
#define ALIGN 402
#define ASM 403
#define ASSERT 404
#define AUTO 405
#define BODY 406
#define BOOL 407
#define BREAK 408
#define BYTE 409
#define CASE 410
#define CAST 411
#define CATCH 412
#define CDOUBLE 413
#define CENT 414
#define CFLOAT 415
#define CHAR 416
#define CLASS 417
#define CONST 418
#define CONTINUE 419
#define CREAL 420
#define DCHAR 421
#define DEBUG 422
#define DEFAULT 423
#define DELEGATE 424
#define DELETE 425
#define DEPRECATED 426
#define DO 427
#define DOUBLE 428
#define ELSE 429
#define ENUM 430
#define EXPORT 431
#define EXTERN 432
#define FALSE 433
#define FINAL 434
#define FINALLY 435
#define FLOAT 436
#define FOR 437
#define FOREACH 438
#define FOREACH_REVERSE 439
#define FUNCTION 440
#define GOTO 441
#define IDOUBLE 442
#define IF 443
#define IFLOAT 444
#define IMMUTABLE 445
#define IMPORT 446
#define IN 447
#define INOUT 448
#define INT 449
#define INTERFACE 450
#define INVARIANT 451
#define IREAL 452
#define IS 453
#define LAZY 454
#define LONG 455
#define MACRO 456
#define MIXIN 457
#define MODULE 458
#define NEW 459
#define NOTHROW 460
#define NULLD 461
#define OUT 462
#define OVERRIDE 463
#define PACKAGE 464
#define PRAGMA 465
#define PRIVATE 466
#define PROTECTED 467
#define PUBLIC 468
#define PURE 469
#define REAL 470
#define REF 471
#define RETURN 472
#define SCOPE 473
#define SHARED 474
#define SHORT 475
#define STATIC 476
#define STRUCT 477
#define SUPER 478
#define SWITCH 479
#define SYNCHRONIZED 480
#define TEMPLATE 481
#define THIS 482
#define THROW 483
#define TRUE 484
#define TRY 485
#define TYPEDEF 486
#define TYPEID 487
#define TYPEOF 488
#define UBYTE 489
#define UCENT 490
#define UINT 491
#define ULONG 492
#define UNION 493
#define UNITTEST 494
#define USHORT 495
#define VERSION 496
#define VOID 497
#define VOLATILE 498
#define WCHAR 499
#define WHILE 500
#define WITH 501

/********** OTHERS **********/
#define NUMBER 547
#define STRING 548
#define COMMENT 549
#define ID 550

/********** SPECIAL SYMBOLS **********/
#define SPECIAL_SYMBOL_ADDITION 551
#define SPECIAL_SYMBOL_ADDITION_EQUAL 552
#define SPECIAL_SYMBOL_SUBTRACTION 553
#define SPECIAL_SYMBOL_SUBTRACTION_EQUAL 554
#define SPECIAL_SYMBOL_GREATER_EQUAL 555
#define SPECIAL_SYMBOL_LESS_EQUAL 556
#define SPECIAL_SYMBOL_EQUAL_EQUAL 557
#define SPECIAL_SYMBOL_NOT_EQUAL 558
#define SPECIAL_SYMBOL_AND 559
#define SPECIAL_SYMBOL_OR 560
#define SPECIAL_SYMBOL_PRINT_FLOAT 561
#define SPECIAL_SYMBOL_PRINT_INT 562
#define SPECIAL_SYMBOL_PRINT_STRING 563
#define SPECIAL_SYMBOL_PRINT_CHAR 564

void initSymbolsTable(TablaHash TS);

int searchTokenCode(TablaHash TS, char* key);

void destroySymbolsTable(TablaHash TS);

#endif //CM1_SYMBOLSTABLE_H
