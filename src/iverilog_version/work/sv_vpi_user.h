/***************************************************************************
* sv_vpi_user.h
*
* SystemVerilog VPI extensions.
*
* This file contains the constant definitions, structure definitions, and
* routine declarations used by the Verilog PLI procedural interface VPI
* access routines.
*
**************************************************************************/
/***************************************************************************
* NOTE:
* The constant values 600 through 999 are reserved for use in this file.
* - the range 600-749 is reserved for SV VPI model extensions
* - the range 750-779 is reserved for the Coverage VPI
* - the range 800-899 is reserved for the Reader VPI
* Overlaps in the numerical ranges are permitted for different categories
* of identifiers; e.g.
* - object types
* - properties
* - callbacks
**************************************************************************/

#ifndef SV_VPI_USER_H
#define SV_VPI_USER_H
#include "vpi_user.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************** OBJECT TYPES ******************************/

#define vpiPackage      600
#define vpiInterface        601
#define vpiProgram      602
#define vpiInterfaceArray   603
#define vpiProgramArray     604
#define vpiTypespec         605
#define vpiModport      606  /* Make same as VCS vpiModPort, it is 606 in LRM */
#define vpiInterfaceTfDecl  607
#define vpiRefObj       608
#define vpiTypeParameter    609 /* SV LRM P1800-2009 */

/* variables */

#define vpiVarBit       vpiRegBit
#define vpiLongIntVar       610
#define vpiShortIntVar      611
#define vpiIntVar       612
#define vpiShortRealVar     613
#define vpiByteVar      614
#define vpiClassVar         615
#define vpiStringVar        616
#define vpiEnumVar      617
#define vpiStructVar        618
#define vpiUnionVar         619
#define vpiBitVar       620
#define vpiLogicVar         vpiReg
#define vpiArrayVar         vpiRegArray
#define vpiClassObj         621
#define vpiChandleVar       622
#define vpiPackedArrayVar   623
#define vpiVirtualInterfaceVar 728

/* typespecs */
#define vpiLongIntTypespec  625
#define vpiShortRealTypespec    626
#define vpiByteTypespec     627
#define vpiShortIntTypespec     628
#define vpiIntTypespec      629
#define vpiClassTypespec    630
#define vpiStringTypespec   631
#define vpiChandleTypespec  632
#define vpiEnumTypespec     633
#define vpiEnumConst        634
#define vpiIntegerTypespec  635
#define vpiTimeTypespec     636
#define vpiRealTypespec     637
#define vpiStructTypespec   638
#define vpiUnionTypespec    639
#define vpiBitTypespec      640
#define vpiLogicTypespec    641
#define vpiArrayTypespec    642
#define vpiVoidTypespec     643
#define vpiTypespecMember   644
#define vpiPackedArrayTypespec 692
#define vpiSequenceTypespec    696
#define vpiPropertyTypespec    697
#define vpiEventTypespec       698
#define vpiClockingBlock    650
#define vpiClockingIODecl   651
#define vpiClassDefn        652
#define vpiConstraint       653
#define vpiConstraintOrdering   654
#define vpiDistItem         645
#define vpiAliasStmt        646
#define vpiThread       647
#define vpiMethodFuncCall   648
#define vpiMethodTaskCall   649

/* concurrent assertions */

#define vpiAssert       686
#define vpiAssume       687
#define vpiCover        688
#define vpiRestrict     901

#define vpiDisableCondition     689
#define vpiClockingEvent    690

/* property decl, spec */

#define vpiPropertyDecl     655
#define vpiPropertySpec     656
#define vpiPropertyExpr     657
#define vpiMulticlockSequenceExpr 658
#define vpiClockedSeq       659
#define vpiClockedProp      902
#define vpiPropertyInst     660
#define vpiSequenceDecl     661
#define vpiCaseProperty     662
#define vpiCasePropertyItem 905 /* property case item 1800-2009 */
#define vpiActualArgExpr    663
#define vpiSequenceInst     664
#define vpiImmediateAssert  665
#define vpiImmediateAssume  694
#define vpiImmediateCover   695
#define vpiReturn       666

/* pattern */

#define vpiAnyPattern       667
#define vpiTaggedPattern    668
#define vpiStructPattern    669

/* do .. while */

#define vpiDoWhile      670

/* waits */

#define vpiOrderedWait      671
#define vpiWaitFork         672

/* disables */

#define vpiDisableFork      673
#define vpiExpectStmt       674
#define vpiForeachStmt      675
#define vpiReturnStmt       691
#define vpiFinal        676
#define vpiExtends      677
#define vpiDistribution     678
#define vpiSeqFormalDecl        679
#define vpiPropFormalDecl       699
#define vpiArrayNet         vpiNetArray
#define vpiEnumNet      680
#define vpiIntegerNet       681
#define vpiLogicNet         vpiNet
#define vpiTimeNet      682
#define vpiStructNet        683
#define vpiBreak            684
#define vpiContinue         685
#define vpiPackedArrayNet   693

/**************** constraint related **************************************/
#define vpiConstraintExpr       747
#define vpiElseConst            748
#define vpiImplication          749
#define vpiConstrIf             738
#define vpiConstrIfElse         739
#define vpiConstrForEach        736
#define vpiSoftDisable          733

#define vpiLetDecl      903
#define vpiLetExpr      904

/******************************** METHODS *********************************/
/************* methods used to traverse 1 to 1 relationships **************/

#define vpiActual       700
#define vpiTypedefAlias     701
#define vpiIndexTypespec    702
#define vpiBaseTypespec     703
#define vpiElemTypespec     704
#define vpiInputSkew        706
#define vpiOutputSkew       707

#define vpiGlobalClocking    708
#define vpiDefaultClocking   709
#define vpiDefaultDisableIff 710

#define vpiOrigin       713
#define vpiPrefix       714
#define vpiWith         715
#define vpiProperty         718
#define vpiValueRange       720
#define vpiPattern      721
#define vpiWeight       722
#define vpiConstraintItem       746

/************ methods used to traverse 1 to many relationships ************/

#define vpiTypedef      725
#define vpiImport       726
#define vpiDerivedClasses   727
#define vpiInterfaceDecl    vpiVirtualInterfaceVar /* interface decl deprecated */
#define vpiMethods      730
#define vpiSolveBefore      731
#define vpiSolveAfter       732
#define vpiWaitingProcesses     734
#define vpiMessages         735
#define vpiLoopVars         737
#define vpiConcurrentAssertions 740
#define vpiMatchItem        741
#define vpiMember       742
#define vpiElement      743

/************ methods used to traverse 1 to many relationships ************/
#define vpiAssertion                744

/************ methods both 1-1 and 1-many relations ***********************/

#define vpiInstance         745

/**************************************************************************/
/************************ generic object properties ***********************/
/**************************************************************************/

#define vpiTop          600
#define vpiUnit         602
#define vpiJoinType     603
#define vpiJoin         0
#define vpiJoinNone     1
#define vpiJoinAny      2

#define vpiAccessType       604
#define vpiForkJoinAcc      1
#define vpiExternAcc        2
#define vpiDPIExportAcc     3
#define vpiDPIImportAcc     4

#define vpiArrayType        606
#define vpiStaticArray      1
#define vpiDynamicArray     2
#define vpiAssocArray       3
#define vpiQueueArray       4

#define vpiArrayMember      607

#define vpiIsRandomized     608
#define vpiLocalVarDecls    609 /* SystemVerilog P1800-2009 */
#define vpiOpStrong         656 /* strength of temporal operator */
#define vpiRandType         610
#define vpiNotRand      1
#define vpiRand         2
#define vpiRandC        3

#define vpiPortType             611
#define vpiInterfacePort 1
#define vpiModportPort   2
/* vpiPort is also a port type. It is defined in vpi_user.h */

#define vpiConstantVariable     612
#define vpiStructUnionMember    615
#define vpiVisibility       620
#define vpiPublicVis        1
#define vpiProtectedVis     2
#define vpiLocalVis         3

#define vpiOneStepConst      9
#define vpiUnboundedConst   10
#define vpiNullConst        11

#define vpiAlwaysType       624
#define vpiAlwaysComb       2
#define vpiAlwaysFF         3
#define vpiAlwaysLatch      4

#define vpiDistType         625
#define vpiEqualDist        1   /* constraint equal distribution */
#define vpiDivDist      2   /* constraint divided distribution */

#define vpiPacked       630
#define vpiTagged       632
#define vpiRef            6 /* return value for vpiDirection property */
#define vpiVirtual      635
#define vpiHasActual    636
#define vpiIsConstraintEnabled  638
#define vpiSoft         639

#define vpiClassType            640
#define vpiMailboxClass         1
#define vpiSemaphoreClass       2
#define vpiUserDefinedClass     3
#define vpiProcessClass         4

#define vpiMethod       645
#define vpiIsClockInferred  649
#define vpiIsFinal          658
#define vpiIsDeferred       657 /* SystemVerilog P1800-2009 */
#define vpiIsCoverSequence  659 /* SystemVerilog P1800-2009 */
#define vpiQualifier        650
#define vpiNoQualifier      0
#define vpiUniqueQualifier  1
#define vpiPriorityQualifier    2
#define vpiTaggedQualifier  4
#define vpiRandQualifier    8
#define vpiInsideQualifier 16 /* SystemVerilog P1800-2009 */
#define vpiIsProtected      74

/****************** Return values for vpiConstType Property ***************/

#define vpiInputEdge        651
#define vpiOutputEdge       652
#define vpiGeneric          653

/* Compatibility-mode property and values (object argument == NULL) */
#define vpiCompatibilityMode        654
#define vpiMode1364v1995    1
#define vpiMode1364v2001    2
#define vpiMode1365v2005    3
#define vpiMode1800v2005    4
#define vpiMode1800v2009    5

#define vpiPackedArrayMember        655 /* SystemVerilog P1800-2009 */
#define vpiStartLine                661 /* SystemVerilog P1800-2005 */
#define vpiColumn                   662 /* SystemVerilog P1800-2005 */
#define vpiEndLine                  663 /* SystemVerilog P1800-2005 */
#define vpiEndColumn                664 /* SystemVerilog P1800-2005 */

/* memory allocation scheme for transient objects */
#define vpiAllocScheme              658 /* SystemVerilog P1800-2009 */
#define vpiAutomaticScheme  1
#define vpiDynamicScheme    2
#define vpiOtherScheme      3

#define vpiObjId                    660 /* SystemVerilog P1800-2009 */

#define vpiDPIPure                  665 /* SystemVerilog P1800-2009 */
#define vpiDPIContext               666 /* SystemVerilog P1800-2009 */
#define vpiDPICStr                  667 /* SystemVerilog P1800-2009 */
#define vpiDPI              1
#define vpiDPIC             2
#define vpiDPICIdentifier           668 /* SystemVerilog P1800-2009 */

/******************************** Operators *******************************/

#define vpiImplyOp      50 /* -> implication operator */
#define vpiNonOverlapImplyOp    51 /* |=> non-overlapped implication */
#define vpiOverlapImplyOp   52 /* |-> overlapped implication operator */
#define vpiAcceptOnOp       83
#define vpiRejectOnOp       84
#define vpiSyncAcceptOnOp   85
#define vpiSyncRejectOnOp   86
#define vpiOverlapFollowedByOp 87
#define vpiNonOverlapFollowedByOp 88
#define vpiNexttimeOp             89
#define vpiAlwaysOp               90
#define vpiEventuallyOp           91
#define vpiUntilOp                92
#define vpiUntilWithOp            93

#define vpiUnaryCycleDelayOp    53 /* binary cycle delay (##) operator */
#define vpiCycleDelayOp     54 /* binary cycle delay (##) operator */
#define vpiIntersectOp      55 /* intersection operator */
#define vpiFirstMatchOp     56 /* first_match operator */
#define vpiThroughoutOp     57 /* throught operator */
#define vpiWithinOp         58 /* within operator */
#define vpiRepeatOp         59 /* [=] non-consecutive repetition */
#define vpiConsecutiveRepeatOp  60 /* [*] consecutive repetition */
#define vpiGotoRepeatOp     61 /* [->] goto repetition */
#define vpiPostIncOp        62 /* ++ post-increment */
#define vpiPreIncOp         63 /* ++ pre-increment */
#define vpiPostDecOp        64 /* -- post-decrement */
#define vpiPreDecOp         65 /* -- pre-decrement */
#define vpiMatchOp      66 /* match() operator */
#define vpiCastOp       67 /* type() operator */
#define vpiIffOp        68 /* iff operator */
#define vpiWildEqOp         69 /* ==? operator */
#define vpiWildNeqOp        70 /* !=? operator */
#define vpiStreamLROp       71 /* left-to-right streaming {>>} operator */
#define vpiStreamRLOp       72 /* right-to-left streaming {<<} operator */
#define vpiMatchedOp        73 /* the .matched sequence operation */
#define vpiTriggeredOp      74 /* the .ended sequence operation */

#define vpiAssignmentPatternOp  75 /* '{} assignment pattern */
#define vpiMultiAssignmentPatternOp 76 /* '{n{}} multi assignment pattern */
#define vpiIfOp                     77
#define vpiIfElseOp                 78
#define vpiCompAndOp                79
#define vpiCompOrOp                 80
#define vpiImpliesOp                94
#define vpiInsideOp                 95
#define vpiTypeOp                   81
#define vpiAssignmentOp             82

/*********************** task/function properties ***********************/

#define vpiOtherFunc        6 /* returns other types;
* for property vpiFuncType */

#define vpiValidUnknown     2 /* Validity of variable is unknown */

/************************** STRUCTURE DEFINITIONS *************************/
/***************************** structure *****************************/
/**************************** CALLBACK REASONS ****************************/

#define cbStartOfThread     600 /* callback on thread creation */
#define cbEndOfThread       601 /* callback on thread termination */
#define cbEnterThread       602 /* callback on re-entering thread */
#define cbStartOfFrame      603 /* callback on frame creation */
#define cbEndOfFrame        604 /* callback on frame exit */
#define cbSizeChange        605 /* callback on variable type/size change */
#define cbCreateObj         700
#define cbReclaimObj        701

/************************* From IEEE P1800-2009 ******************************/
#define cbEndOfObject       702 /* callback on transient object deletion */

/************************* FUNCTION DECLARATIONS **************************/
/**************************************************************************/
/*************************** Coverage VPI *********************************/
/**************************************************************************/

/* coverage control */

#define vpiCoverageStart    750
#define vpiCoverageStop     751
#define vpiCoverageReset    752
#define vpiCoverageCheck    753
#define vpiCoverageMerge    754
#define vpiCoverageSave     755

/* coverage type properties */

#define vpiAssertCoverage   760
#define vpiFsmStateCoverage     761
#define vpiStatementCoverage    762
#define vpiToggleCoverage   763

/* coverage status properties */

#define vpiCovered      765
#define vpiCoverMax         766
#define vpiCoveredCount     767

/* assertion-specific coverage status properties */

#define vpiAssertAttemptCovered 770
#define vpiAssertSuccessCovered 771
#define vpiAssertFailureCovered 772

/* vpiAssertVacuousSuccessCovered, was referenced in      */
/* SystemVerilog 3.1a & P1800-2005 LRM but not defined.   */
#define vpiAssertVacuousSuccessCovered       773 /* SystemVerilog P1800-2009 */
#define vpiAssertDisableCovered              774 /* SystemVerilog P1800-2009 */
#define vpiAssertKillCovered                 777 /* SystemVerilog P1800-2009 */

/* FSM-specific coverage status properties */

#define vpiFsmStates        775
#define vpiFsmStateExpression   776

/* FSM handle types */

#define vpiFsm          758
#define vpiFsmHandle        759

/***************************************************************************/
/***************************** Assertion VPI *******************************/
/***************************************************************************/

/* assertion callback types */

#define cbAssertionStart    606
#define cbAssertionSuccess  607
#define cbAssertionFailure  608
#define cbAssertionVacuousSuccess             657 /* SystemVerilog P1800-2009 */
#define cbAssertionDisabledEvaluation         658 /* SystemVerilog P1800-2009 */
#define cbAssertionPropStart    615
#define cbAssertionPropSuccess  616
#define cbAssertionPropFailure  617
#define cbAssertionStepSuccess  609
#define cbAssertionStepFailure  610
#define cbAssertionLock         661
#define cbAssertionUnlock       662
#define cbAssertionDisable  611
#define cbAssertionEnable   612
#define cbAssertionReset    613
#define cbAssertionKill     614
#define cbAssertionEnablePassAction           645 /* SystemVerilog P1800-2009 */
#define cbAssertionEnableFailAction           646 /* SystemVerilog P1800-2009 */
#define cbAssertionDisablePassAction          647 /* SystemVerilog P1800-2009 */
#define cbAssertionDisableFailAction          648 /* SystemVerilog P1800-2009 */
#define cbAssertionEnableNonvacuousAction     649 /* SystemVerilog P1800-2009 */
#define cbAssertionDisableVacuousAction       650 /* SystemVerilog P1800-2009 */

/* assertion "system" callback types */

#define cbAssertionSysInitialized 615
#define cbAssertionSysOn          616
#define cbAssertionSysOff         617
#define cbAssertionSysKill        631
#define cbAssertionSysLock        659
#define cbAssertionSysUnlock      660
#define cbAssertionSysEnd   618
#define cbAssertionSysReset     619
#define cbAssertionSysEnablePassAction        651 /* SystemVerilog P1800-2009 */
#define cbAssertionSysEnableFailAction        652 /* SystemVerilog P1800-2009 */
#define cbAssertionSysDisablePassAction       653 /* SystemVerilog P1800-2009 */
#define cbAssertionSysDisableFailAction       654 /* SystemVerilog P1800-2009 */
#define cbAssertionSysEnableNonvacuousAction  655 /* SystemVerilog P1800-2009 */
#define cbAssertionSysDisableVacuousAction    656 /* SystemVerilog P1800-2009 */

/* assertion control constants */

#define vpiAssertionLock        645
#define vpiAssertionUnlock      646
#define vpiAssertionDisable     620
#define vpiAssertionEnable  621
#define vpiAssertionReset   622
#define vpiAssertionKill    623
#define vpiAssertionEnableStep  624
#define vpiAssertionDisableStep 625
#define vpiAssertionClockSteps  626
#define vpiAssertionSysLock     647
#define vpiAssertionSysUnlock   648
#define vpiAssertionSysOn       627
#define vpiAssertionSysOff      628
#define vpiAssertionSysKill     632
#define vpiAssertionSysEnd  629
#define vpiAssertionSysReset    630
#define vpiAssertionDisablePassAction 633 /* SystemVerilog P1800-2009 */
#define vpiAssertionEnablePassAction  634 /* SystemVerilog P1800-2009 */
#define vpiAssertionDisableFailAction 635 /* SystemVerilog P1800-2009 */
#define vpiAssertionEnableFailAction  636 /* SystemVerilog P1800-2009 */
#define vpiAssertionDisableVacuousAction 637 /* SystemVerilog P1800-2009 */
#define vpiAssertionEnableNonvacuousAction 638 /* SystemVerilog P1800-2009 */
#define vpiAssertionSysEnablePassAction 639 /* SystemVerilog P1800-2009 */
#define vpiAssertionSysEnableFailAction 640 /* SystemVerilog P1800-2009 */
#define vpiAssertionSysDisablePassAction 641 /* SystemVerilog P1800-2009 */
#define vpiAssertionSysDisableFailAction 642 /* SystemVerilog P1800-2009 */
#define vpiAssertionSysEnableNonvacuousAction 643 /* SystemVerilog P1800-2009 */
#define vpiAssertionSysDisableVacuousAction 644 /* SystemVerilog P1800-2009 */

/* assertion related structs and types */

typedef struct t_vpi_source_info {
    PLI_BYTE8 *fileName;
    PLI_INT32 startLine;
    PLI_INT32 startColumn;
    PLI_INT32 endLine;
    PLI_INT32 endColumn;
} s_vpi_source_info, *p_vpi_source_info;

typedef struct t_vpi_assertion_info {
    PLI_BYTE8 *assertName;   /* name of assertion */
    vpiHandle instance;      /* instance containing assertion */
    PLI_BYTE8 *defname;      /* name of module/interface containing
                      * the assertion */
    vpiHandle clock;     /* clocking expression */
    PLI_INT32 assertionType; /* vpiSequenceInst, vpiAssert, vpiAssume,
                  * vpiCover, vpiPropertyInst,
                  * vpiImmediateAssert */
    s_vpi_source_info sourceInfo;
} s_vpi_assertion_info, *p_vpi_assertion_info;

typedef struct t_vpi_assertion_step_info {
    PLI_INT32 matched_expression_count;
    vpiHandle *matched_exprs;       /* array of expressions */
    p_vpi_source_info *exprs_source_info;   /* array of source info */
    PLI_INT32 stateFrom, stateTo;       /* identify transition */
} s_vpi_assertion_step_info, *p_vpi_assertion_step_info;

typedef struct t_vpi_attempt_local_var_info {
    vpiHandle localVar;
} s_vpi_attempt_local_var_info, *p_vpi_attempt_local_var_info;

typedef struct t_vpi_attempt_info {
    union {
        vpiHandle failExpr;
        p_vpi_assertion_step_info step;
        p_vpi_attempt_local_var_info local_var_info;
    } detail;
    s_vpi_time attemptStartTime;        /* Time attempt triggered */
} s_vpi_attempt_info, *p_vpi_attempt_info;

/* typedef for vpi_register_assertion_cb callback function */

typedef PLI_INT32(vpi_assertion_callback_func)(
    PLI_INT32 reason,    /* callback reason */
    p_vpi_time cb_time,      /* callback time */
    vpiHandle assertion,     /* handle to assertion */
    p_vpi_attempt_info info, /* attempt related information */
    PLI_BYTE8 *user_data     /* user data entered upon registration */
);

/* assertion specific VPI functions */

PLI_INT32 vpi_get_assertion_info(
    vpiHandle assertion,       /* handle to assertion */
    p_vpi_assertion_info info  /* assertion related information */
);

vpiHandle vpi_register_assertion_cb(
    vpiHandle assertion,       /* handle to assertion */
    PLI_INT32 reason,      /* reason for which callbacks needed */
    vpi_assertion_callback_func *cb_rtn,
    PLI_BYTE8 *user_data       /* user data to be supplied to cb */
);

void vpi_free_vir_ip_memory(void);

/* See lib/vcsd.h for details. */
#ifndef vcsd_alp_bits_t__DEFINED
#    define vcsd_alp_bits_t__DEFINED
typedef unsigned vcsd_alp_bits_t;
#endif

/***************************************************************************/
/******************************* Reader VPI ********************************/
/***************************************************************************/

/********** Reader types ***********/

#define vpiTrvsObj      800 /* Data traverse object */
#define vpiCollection       810 /* Collection of VPI handle */
#define vpiObjCollection    811 /* Collection of traversable design objs */
#define vpiTrvsCollection   812 /* Collection of vpiTrvsObjs */

/********* Reader methods *********/

/* Check */

#define vpiIsLoaded         820 /* Object data is loaded check */
#define vpiHasDataVC        821 /* Traverse object has at least one VC
* at some point in time in the
* database check */
#define vpiHasVC        822 /* Has VC at specific time check */
#define vpiHasNoValue       823 /* Has no value at specific time check */
#define vpiBelong       824 /* Belongs to extension check */

/* Access */

#define vpiAccessLimitedInteractive 830 /* Interactive access */
#define vpiAccessInteractive    831 /* interactive with history access */
#define vpiAccessPostProcess    832 /* Database access */

/* Iteration on instances for loaded */

#define vpiDataLoaded       850 /* Use in vpi_iterate() */

/* Control Traverse/Check Time */

#define vpiMinTime      860 /* Min time */
#define vpiMaxTime      864 /* Max time */
#define vpiPrevVC       868 /* Previous Value Change (VC) */
#define vpiNextVC       870 /* Next Value Change (VC) */
#define vpiTime         874 /* Time jump */

/********** Reader routines **********/

/* load extension form for the reader extension */

PLI_INT32 vpi_load_extension(
    PLI_BYTE8 *extension_name,
    PLI_BYTE8 *name,
    PLI_INT32 mode,
    ...);

PLI_INT32 vpi_close(
    PLI_INT32 tool,
    PLI_INT32 prop,
    PLI_BYTE8* name
);

PLI_INT32 vpi_load_init(
    vpiHandle objCollection,
    vpiHandle scope,
    PLI_INT32 level
);

PLI_INT32 vpi_load(vpiHandle h);
PLI_INT32 vpi_unload(vpiHandle h);

vpiHandle vpi_create(
    PLI_INT32 prop,
    vpiHandle h,
    vpiHandle obj
);

vpiHandle vpi_goto(
    PLI_INT32 prop,
    vpiHandle obj,
    p_vpi_time time_p,
    PLI_INT32 *ret_code
);

vpiHandle vpi_filter(
    vpiHandle h,
    PLI_INT32 ft,
    PLI_INT32 flag
);

#ifdef __cplusplus
}
#endif
#endif
