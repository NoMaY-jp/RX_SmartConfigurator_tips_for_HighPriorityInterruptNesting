MEMORY
{
	RAM : ORIGIN = 0x4, LENGTH = 0x7fffc
	RAM2 : ORIGIN = 0x00800000, LENGTH = 524288
	ROM : ORIGIN = 0xFFC00000, LENGTH = 4194304
	OFS : ORIGIN = 0xFE7F5D00, LENGTH = 128
}
SECTIONS
{
	.exvectors 0xFFFFFF80: AT(0xFFFFFF80)
	{
		"_exvectors_start" = .;
		KEEP(*(.exvectors))
	"_exvectors_end" = .;
	} >ROM
	.fvectors 0xFFFFFFFC: AT(0xFFFFFFFC)
	{
		KEEP(*(.fvectors))
	} > ROM
	.text 0xFFC00000: AT(0xFFC00000)
	{
		*(.text)
		/* for High Priority Nested Interrupt Support Library */
		. = ALIGN(4);
		KEEP(*(.text.hook_entry___0))
		KEEP(*(.text.hook_entry___1))
		KEEP(*(.text.hook_entry___2))
		KEEP(*(.text.hook_entry___3))
		KEEP(*(.text.hook_entry___4))
		KEEP(*(.text.hook_entry___5))
		KEEP(*(.text.hook_entry___6))
		KEEP(*(.text.hook_entry___7))
		KEEP(*(.text.hook_entry___8))
		KEEP(*(.text.hook_entry___9))
		KEEP(*(.text.hook_entry__10))
		KEEP(*(.text.hook_entry__11))
		KEEP(*(.text.hook_entry__12))
		KEEP(*(.text.hook_entry__13))
		KEEP(*(.text.hook_entry__14))
		KEEP(*(.text.hook_entry__15))
		KEEP(*(.text.hook_entry__16))
		KEEP(*(.text.hook_entry__17))
		KEEP(*(.text.hook_entry__18))
		KEEP(*(.text.hook_entry__19))
		KEEP(*(.text.hook_entry__20))
		KEEP(*(.text.hook_entry__21))
		KEEP(*(.text.hook_entry__22))
		KEEP(*(.text.hook_entry__23))
		KEEP(*(.text.hook_entry__24))
		KEEP(*(.text.hook_entry__25))
		KEEP(*(.text.hook_entry__26))
		KEEP(*(.text.hook_entry__27))
		KEEP(*(.text.hook_entry__28))
		KEEP(*(.text.hook_entry__29))
		KEEP(*(.text.hook_entry__30))
		KEEP(*(.text.hook_entry__31))
		KEEP(*(.text.hook_entry__32))
		KEEP(*(.text.hook_entry__33))
		KEEP(*(.text.hook_entry__34))
		KEEP(*(.text.hook_entry__35))
		KEEP(*(.text.hook_entry__36))
		KEEP(*(.text.hook_entry__37))
		KEEP(*(.text.hook_entry__38))
		KEEP(*(.text.hook_entry__39))
		KEEP(*(.text.hook_entry__40))
		KEEP(*(.text.hook_entry__41))
		KEEP(*(.text.hook_entry__42))
		KEEP(*(.text.hook_entry__43))
		KEEP(*(.text.hook_entry__44))
		KEEP(*(.text.hook_entry__45))
		KEEP(*(.text.hook_entry__46))
		KEEP(*(.text.hook_entry__47))
		KEEP(*(.text.hook_entry__48))
		KEEP(*(.text.hook_entry__49))
		KEEP(*(.text.hook_entry__50))
		KEEP(*(.text.hook_entry__51))
		KEEP(*(.text.hook_entry__52))
		KEEP(*(.text.hook_entry__53))
		KEEP(*(.text.hook_entry__54))
		KEEP(*(.text.hook_entry__55))
		KEEP(*(.text.hook_entry__56))
		KEEP(*(.text.hook_entry__57))
		KEEP(*(.text.hook_entry__58))
		KEEP(*(.text.hook_entry__59))
		KEEP(*(.text.hook_entry__60))
		KEEP(*(.text.hook_entry__61))
		KEEP(*(.text.hook_entry__62))
		KEEP(*(.text.hook_entry__63))
		KEEP(*(.text.hook_entry__64))
		KEEP(*(.text.hook_entry__65))
		KEEP(*(.text.hook_entry__66))
		KEEP(*(.text.hook_entry__67))
		KEEP(*(.text.hook_entry__68))
		KEEP(*(.text.hook_entry__69))
		KEEP(*(.text.hook_entry__70))
		KEEP(*(.text.hook_entry__71))
		KEEP(*(.text.hook_entry__72))
		KEEP(*(.text.hook_entry__73))
		KEEP(*(.text.hook_entry__74))
		KEEP(*(.text.hook_entry__75))
		KEEP(*(.text.hook_entry__76))
		KEEP(*(.text.hook_entry__77))
		KEEP(*(.text.hook_entry__78))
		KEEP(*(.text.hook_entry__79))
		KEEP(*(.text.hook_entry__80))
		KEEP(*(.text.hook_entry__81))
		KEEP(*(.text.hook_entry__82))
		KEEP(*(.text.hook_entry__83))
		KEEP(*(.text.hook_entry__84))
		KEEP(*(.text.hook_entry__85))
		KEEP(*(.text.hook_entry__86))
		KEEP(*(.text.hook_entry__87))
		KEEP(*(.text.hook_entry__88))
		KEEP(*(.text.hook_entry__89))
		KEEP(*(.text.hook_entry__90))
		KEEP(*(.text.hook_entry__91))
		KEEP(*(.text.hook_entry__92))
		KEEP(*(.text.hook_entry__93))
		KEEP(*(.text.hook_entry__94))
		KEEP(*(.text.hook_entry__95))
		KEEP(*(.text.hook_entry__96))
		KEEP(*(.text.hook_entry__97))
		KEEP(*(.text.hook_entry__98))
		KEEP(*(.text.hook_entry__99))
		KEEP(*(.text.hook_entry_100))
		KEEP(*(.text.hook_entry_101))
		KEEP(*(.text.hook_entry_102))
		KEEP(*(.text.hook_entry_103))
		KEEP(*(.text.hook_entry_104))
		KEEP(*(.text.hook_entry_105))
		KEEP(*(.text.hook_entry_106))
		KEEP(*(.text.hook_entry_107))
		KEEP(*(.text.hook_entry_108))
		KEEP(*(.text.hook_entry_109))
		KEEP(*(.text.hook_entry_110))
		KEEP(*(.text.hook_entry_111))
		KEEP(*(.text.hook_entry_112))
		KEEP(*(.text.hook_entry_113))
		KEEP(*(.text.hook_entry_114))
		KEEP(*(.text.hook_entry_115))
		KEEP(*(.text.hook_entry_116))
		KEEP(*(.text.hook_entry_117))
		KEEP(*(.text.hook_entry_118))
		KEEP(*(.text.hook_entry_119))
		KEEP(*(.text.hook_entry_120))
		KEEP(*(.text.hook_entry_121))
		KEEP(*(.text.hook_entry_122))
		KEEP(*(.text.hook_entry_123))
		KEEP(*(.text.hook_entry_124))
		KEEP(*(.text.hook_entry_125))
		KEEP(*(.text.hook_entry_126))
		KEEP(*(.text.hook_entry_127))
		KEEP(*(.text.hook_entry_128))
		KEEP(*(.text.hook_entry_129))
		KEEP(*(.text.hook_entry_130))
		KEEP(*(.text.hook_entry_131))
		KEEP(*(.text.hook_entry_132))
		KEEP(*(.text.hook_entry_133))
		KEEP(*(.text.hook_entry_134))
		KEEP(*(.text.hook_entry_135))
		KEEP(*(.text.hook_entry_136))
		KEEP(*(.text.hook_entry_137))
		KEEP(*(.text.hook_entry_138))
		KEEP(*(.text.hook_entry_139))
		KEEP(*(.text.hook_entry_140))
		KEEP(*(.text.hook_entry_141))
		KEEP(*(.text.hook_entry_142))
		KEEP(*(.text.hook_entry_143))
		KEEP(*(.text.hook_entry_144))
		KEEP(*(.text.hook_entry_145))
		KEEP(*(.text.hook_entry_146))
		KEEP(*(.text.hook_entry_147))
		KEEP(*(.text.hook_entry_148))
		KEEP(*(.text.hook_entry_149))
		KEEP(*(.text.hook_entry_150))
		KEEP(*(.text.hook_entry_151))
		KEEP(*(.text.hook_entry_152))
		KEEP(*(.text.hook_entry_153))
		KEEP(*(.text.hook_entry_154))
		KEEP(*(.text.hook_entry_155))
		KEEP(*(.text.hook_entry_156))
		KEEP(*(.text.hook_entry_157))
		KEEP(*(.text.hook_entry_158))
		KEEP(*(.text.hook_entry_159))
		KEEP(*(.text.hook_entry_160))
		KEEP(*(.text.hook_entry_161))
		KEEP(*(.text.hook_entry_162))
		KEEP(*(.text.hook_entry_163))
		KEEP(*(.text.hook_entry_164))
		KEEP(*(.text.hook_entry_165))
		KEEP(*(.text.hook_entry_166))
		KEEP(*(.text.hook_entry_167))
		KEEP(*(.text.hook_entry_168))
		KEEP(*(.text.hook_entry_169))
		KEEP(*(.text.hook_entry_170))
		KEEP(*(.text.hook_entry_171))
		KEEP(*(.text.hook_entry_172))
		KEEP(*(.text.hook_entry_173))
		KEEP(*(.text.hook_entry_174))
		KEEP(*(.text.hook_entry_175))
		KEEP(*(.text.hook_entry_176))
		KEEP(*(.text.hook_entry_177))
		KEEP(*(.text.hook_entry_178))
		KEEP(*(.text.hook_entry_179))
		KEEP(*(.text.hook_entry_180))
		KEEP(*(.text.hook_entry_181))
		KEEP(*(.text.hook_entry_182))
		KEEP(*(.text.hook_entry_183))
		KEEP(*(.text.hook_entry_184))
		KEEP(*(.text.hook_entry_185))
		KEEP(*(.text.hook_entry_186))
		KEEP(*(.text.hook_entry_187))
		KEEP(*(.text.hook_entry_188))
		KEEP(*(.text.hook_entry_189))
		KEEP(*(.text.hook_entry_190))
		KEEP(*(.text.hook_entry_191))
		KEEP(*(.text.hook_entry_192))
		KEEP(*(.text.hook_entry_193))
		KEEP(*(.text.hook_entry_194))
		KEEP(*(.text.hook_entry_195))
		KEEP(*(.text.hook_entry_196))
		KEEP(*(.text.hook_entry_197))
		KEEP(*(.text.hook_entry_198))
		KEEP(*(.text.hook_entry_199))
		KEEP(*(.text.hook_entry_200))
		KEEP(*(.text.hook_entry_201))
		KEEP(*(.text.hook_entry_202))
		KEEP(*(.text.hook_entry_203))
		KEEP(*(.text.hook_entry_204))
		KEEP(*(.text.hook_entry_205))
		KEEP(*(.text.hook_entry_206))
		KEEP(*(.text.hook_entry_207))
		KEEP(*(.text.hook_entry_208))
		KEEP(*(.text.hook_entry_209))
		KEEP(*(.text.hook_entry_210))
		KEEP(*(.text.hook_entry_211))
		KEEP(*(.text.hook_entry_212))
		KEEP(*(.text.hook_entry_213))
		KEEP(*(.text.hook_entry_214))
		KEEP(*(.text.hook_entry_215))
		KEEP(*(.text.hook_entry_216))
		KEEP(*(.text.hook_entry_217))
		KEEP(*(.text.hook_entry_218))
		KEEP(*(.text.hook_entry_219))
		KEEP(*(.text.hook_entry_220))
		KEEP(*(.text.hook_entry_221))
		KEEP(*(.text.hook_entry_222))
		KEEP(*(.text.hook_entry_223))
		KEEP(*(.text.hook_entry_224))
		KEEP(*(.text.hook_entry_225))
		KEEP(*(.text.hook_entry_226))
		KEEP(*(.text.hook_entry_227))
		KEEP(*(.text.hook_entry_228))
		KEEP(*(.text.hook_entry_229))
		KEEP(*(.text.hook_entry_230))
		KEEP(*(.text.hook_entry_231))
		KEEP(*(.text.hook_entry_232))
		KEEP(*(.text.hook_entry_233))
		KEEP(*(.text.hook_entry_234))
		KEEP(*(.text.hook_entry_235))
		KEEP(*(.text.hook_entry_236))
		KEEP(*(.text.hook_entry_237))
		KEEP(*(.text.hook_entry_238))
		KEEP(*(.text.hook_entry_239))
		KEEP(*(.text.hook_entry_240))
		KEEP(*(.text.hook_entry_241))
		KEEP(*(.text.hook_entry_242))
		KEEP(*(.text.hook_entry_243))
		KEEP(*(.text.hook_entry_244))
		KEEP(*(.text.hook_entry_245))
		KEEP(*(.text.hook_entry_246))
		KEEP(*(.text.hook_entry_247))
		KEEP(*(.text.hook_entry_248))
		KEEP(*(.text.hook_entry_249))
		KEEP(*(.text.hook_entry_250))
		KEEP(*(.text.hook_entry_251))
		KEEP(*(.text.hook_entry_252))
		KEEP(*(.text.hook_entry_253))
		KEEP(*(.text.hook_entry_254))
		KEEP(*(.text.hook_entry_255))
		KEEP(*(.text.INT_COMMON_NESTEDINT_PERMIT))
		KEEP(*(.text.INT_COMMON_NESTEDINT_NOT_PERMIT))
		/* for backward compatibility */
		KEEP(*(.text.*_isr))	   /* for FIT */
		KEEP(*(.text.Excep_*))     /* for FIT Flash modeule */
		KEEP(*(.text.*_interrupt)) /* for CG */
		KEEP(*(.text.*Interrupt))  /* for CG Motor Component */
		KEEP(*(.text.*ISR)) 	   /* for FreeRTOS Kernel and Demos */
		*(.text.*)
		/* for updated FIT, CG and RX SmartConfigurator */
		KEEP(*(.isrtext))
		KEEP(*(.isrtext.*))
		*(P)
		etext = .;
	} > ROM
	.rvectors ALIGN(4):
	{
		_rvectors_start = .;
		INCLUDE ../src/smc_gen/r_bsp/mcu/all/linker_script_rvectors.inc
		_rvectors_end = .;
	} > ROM
	.init :
	{
		KEEP(*(.init))
		__preinit_array_start = .;
		KEEP(*(.preinit_array))
		__preinit_array_end = .;
		__init_array_start = (. + 3) & ~ 3;
		KEEP(*(.init_array))
		KEEP(*(SORT(.init_array.*)))
		__init_array_end = .;
		__fini_array_start = .;
		KEEP(*(.fini_array))
		KEEP(*(SORT(.fini_array.*)))
		__fini_array_end = .;
	} > ROM
	.fini :
	{
		KEEP(*(.fini))
	} > ROM
	.got :
	{
		*(.got)
		*(.got.plt)
	} > ROM
	.rodata :
	{
		*(.rodata)
		*(.rodata.*)
		*(C_1)
		*(C_2)
		*(C)
		_erodata = .;
	} > ROM
	gcc_exceptions_table :
	{
	    KEEP (*(.gcc_except_table))
	    *(.gcc_except_table.*)
	} > ROM
	.eh_frame_hdr :
	{
		*(.eh_frame_hdr)
	} > ROM
	.eh_frame :
	{
		*(.eh_frame)
	} > ROM
	.jcr :
	{
		*(.jcr)
	} > ROM
	.tors :
	{
		__CTOR_LIST__ = .;
		. = ALIGN(2);
		___ctors = .;
		*(.ctors)
		___ctors_end = .;
		__CTOR_END__ = .;
		__DTOR_LIST__ = .;
		___dtors = .;
		*(.dtors)
		___dtors_end = .;
		__DTOR_END__ = .;
		. = ALIGN(2);
		_mdata = .;
	} > ROM
	.data : AT(_mdata)
	{
		_data = .;
		*(.data)
		*(.data.*)
		*(D)
		*(D_1)
		*(D_2)
		_edata = .;
	} > RAM
	.bss :
	{
		_bss = .;
		*(.bss)
		*(.bss.**)
		*(COMMON)
		*(B)
		*(B_1)
		*(B_2)
		_ebss = .;
		. = ALIGN(128);
		_end = .;
	} > RAM AT>RAM
	.ofs1 0xFE7F5D00: AT(0xFE7F5D00)
	{
		KEEP(*(.ofs1))
	} > OFS
	.ofs2 0xFE7F5D10: AT(0xFE7F5D10)
	{
		KEEP(*(.ofs2))
	} > OFS
	.ofs3 0xFE7F5D20: AT(0xFE7F5D20)
	{
		KEEP(*(.ofs3))
	} > OFS
	.ofs4 0xFE7F5D40: AT(0xFE7F5D40)
	{
		KEEP(*(.ofs4))
	} > OFS
	.ofs5 0xFE7F5D48: AT(0xFE7F5D48)
	{
		KEEP(*(.ofs5))
	} > OFS
	.ofs6 0xFE7F5D50: AT(0xFE7F5D50)
	{
		KEEP(*(.ofs6))
	} > OFS
	.ofs7 0xFE7F5D64: AT(0xFE7F5D64)
	{
		KEEP(*(.ofs7))
	} > OFS
	.ofs8 0xFE7F5D70: AT(0xFE7F5D70)
	{
		KEEP(*(.ofs8))
	} > OFS
.r_bsp_NULL :
	{
		. += 0x100;
		"_r_bsp_NULL_end" = .;
	} >RAM AT>RAM
.r_bsp_istack BLOCK(0x4) (NOLOAD) :
	{
		KEEP(*(.r_bsp_istack))
	} >RAM AT>RAM
.istack :
	{
		"_istack" = .;
	} >RAM
.r_bsp_ustack BLOCK(0x4) (NOLOAD) :
	{
		KEEP(*(.r_bsp_ustack))
	} >RAM AT>RAM
.ustack :
	{
		"_ustack" = .;
	} >RAM
}
