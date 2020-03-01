	public _f

   .model tiny
   .stack 0h
   .data
   .code

_f proc
   push bp
   mov bp, sp
   mov ax, [bp + 4]
   add ax, 1
   pop bp
	ret
_f endp
	end

