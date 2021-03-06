; Generated by holtek-gcc v3.19, Fri Jan 21 10:13:28 2022
; 
; Configuration:
;       without long instruction
;       Single ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use tabrd-const
;       
;       
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.19" "build 20130711"
; Rebuild 718

ir equ [2]
mp equ [3]
sbp equ [1]
acc equ [5]
bp equ [4]
tblp equ [7]
tbhp equ [9]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
intc equ [11]

extern ra:byte
extern rb:byte
extern rc:byte
extern rd:byte
extern re:byte
extern rf:byte
extern rg:byte
extern rh:byte
extern _Crom2Prom:near
extern _Crom2PromNext:near

RAMBANK 0 @HCCINIT, @HCCINIT0

RAMBANK 0 @BITDATASEC, @BITDATASEC1
@HCCINIT	.section 'data'
@HCCINIT0	.section 'data'
@BITDATASEC	 .section 'data'
@BITDATASEC1	 .section 'data'

#pragma debug scope 1 1
	extern __DELAY3:near
	extern __DELAYX3:near
	extern __DELAYX6:near
	extern __DELAYY5:near
	extern __DELAYY3:near
	extern _builtin_holtek_delay_2:byte
public _use_delay_us
#pragma debug scope 2 1
#line 10 "E:\HT66F018_F12\main_new\record_control.c"
_use_delay_us .section 'code'
_use_delay_us proc
public _use_delay_us_2
    local _use_delay_us_2 db 2 dup(?)	; 2,0
#pragma debug variable 12 2 _use_delay_us_2+0 "us_s"
#line 11 "E:\HT66F018_F12\main_new\record_control.c"
	clr _user_delay_time[0]
	clr _user_delay_time[1]
#line 12 "E:\HT66F018_F12\main_new\record_control.c"
	mov a,1
	mov _user_delay_flag[0],a
_L3:
#line 13 "E:\HT66F018_F12\main_new\record_control.c"
	mov a,_use_delay_us_2[0]
	sub a,_user_delay_time[0]
	mov a,_use_delay_us_2[1]
	sbc a,_user_delay_time[1]
	sz c
	jmp _L3
#line 17 "E:\HT66F018_F12\main_new\record_control.c"
	clr _user_delay_flag[0]
#line 18 "E:\HT66F018_F12\main_new\record_control.c"
	clr _user_delay_time[0]
	clr _user_delay_time[1]
	ret
_use_delay_us endp
#line 18 "E:\HT66F018_F12\main_new\record_control.c"
#pragma debug scope 1 1
___pb equ [37]
public _set_voice
#pragma debug scope 3 1
#line 22 "E:\HT66F018_F12\main_new\record_control.c"
_set_voice .section 'code'
_set_voice proc
    local _set_voice_2 db 2 dup(?)	; 0,2
	mov _set_voice_2[0],a
#pragma debug variable 8 3 _set_voice_2+0 "date_v"
#line 26 "E:\HT66F018_F12\main_new\record_control.c"
	clr [37].3
#line 27 "E:\HT66F018_F12\main_new\record_control.c"
	mov a,40
	mov _use_delay_us_2[0],a
	clr _use_delay_us_2[1]
	call _use_delay_us
#line 28 "E:\HT66F018_F12\main_new\record_control.c"
	set [37].3
#line 29 "E:\HT66F018_F12\main_new\record_control.c"
	mov a,40
	mov _use_delay_us_2[0],a
	clr _use_delay_us_2[1]
	call _use_delay_us
#line 30 "E:\HT66F018_F12\main_new\record_control.c"
	clr [37].3
#line 31 "E:\HT66F018_F12\main_new\record_control.c"
	mov a,5
	mov _use_delay_us_2[0],a
	clr _use_delay_us_2[1]
	call _use_delay_us
	mov a,8
	mov _set_voice_2[1],a
_L9:
#line 35 "E:\HT66F018_F12\main_new\record_control.c"
	snz _set_voice_2[0].0
	jmp _L6
#line 38 "E:\HT66F018_F12\main_new\record_control.c"
	set [37].3
#line 39 "E:\HT66F018_F12\main_new\record_control.c"
	mov a,20
	mov _use_delay_us_2[0],a
	clr _use_delay_us_2[1]
	jmp _L10
_L6:
#line 46 "E:\HT66F018_F12\main_new\record_control.c"
	set [37].3
#line 47 "E:\HT66F018_F12\main_new\record_control.c"
	mov a,10
	mov _use_delay_us_2[0],a
	clr _use_delay_us_2[1]
_L10:
	call _use_delay_us
#line 48 "E:\HT66F018_F12\main_new\record_control.c"
	clr [37].3
#line 49 "E:\HT66F018_F12\main_new\record_control.c"
	mov a,5
	mov _use_delay_us_2[0],a
	clr _use_delay_us_2[1]
	call _use_delay_us
#line 51 "E:\HT66F018_F12\main_new\record_control.c"
	clr c
	rrc _set_voice_2[0]
	sdz _set_voice_2[1]
	jmp _L9
#line 54 "E:\HT66F018_F12\main_new\record_control.c"
	set [37].3
#line 55 "E:\HT66F018_F12\main_new\record_control.c"
	mov a,40
	mov _use_delay_us_2[0],a
	clr _use_delay_us_2[1]
	call _use_delay_us
	ret
_set_voice endp
#line 55 "E:\HT66F018_F12\main_new\record_control.c"
#pragma debug scope 1 1
public _user_delay_time
@HCCINIT	.section 'data'
#line 5 "E:\HT66F018_F12\main_new\record_control.c"
@HCCINIT .section 'data'
_user_delay_time label byte
#pragma debug variable 12 1 _user_delay_time "user_delay_time"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT .section 'data'
public _user_delay_flag
#line 4 "E:\HT66F018_F12\main_new\record_control.c"
@HCCINIT .section 'data'
_user_delay_flag label byte
#pragma debug variable 8 1 _user_delay_flag "user_delay_flag"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT .section 'data'
#pragma debug struct_begin 42 "__pb_bits"
#pragma debug field 21 8 0 1 "__pb0" ;0,1
#pragma debug field 21 8 0 1 "__pb1" ;1,1
#pragma debug field 21 8 0 1 "__pb2" ;2,1
#pragma debug field 21 8 0 1 "__pb3" ;3,1
#pragma debug field 21 8 0 1 "__pb4" ;4,1
#pragma debug field 21 8 0 1 "__pb5" ;5,1
#pragma debug field 21 8 0 1 "__pb6" ;6,1
#pragma debug field 21 8 0 1 ;7,1
#pragma debug struct_end
#pragma debug union_begin 43 ""
#pragma debug field 2 42 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 43 1 ___pb "__pb" 1

; 
; Generated by holtek-gcc v3.19, Fri Jan 21 10:13:28 2022
; Rebuild 718
; end of file
