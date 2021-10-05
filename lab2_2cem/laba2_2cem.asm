.model small
.stack 256

.data  
N db 3
array dw 1, 10, 100

.code   
        mov ax,@data
        mov ds,ax
        
        mov cx, 3     
        mov di,0x0D
         
inpt:   mov ah, 08h
        int 21h
        mov ah,0
        cmp di,ax
        je body   
        mov si,ax
        push si
        loop inpt
        
        
        
body:   
        mov dx,3
        sub dx,cx 
        mov cx,dx
        lea bx,array
        mov si,0 
        mov di,0
getNumber:      

        pop ax
        sub ax,30h
        mul [bx+si]
        add si,2
        add ax,di
        mov di,ax
        loop getNumber
        
        mov ax,di
        mov si,ax
        
        cmp si,1
        je cout
        
a1:        
        mov cl,2
        div cl 
        mov ah,0
        mov cx,ax
        mov bl,2 
        
findDel:
       mov ax,si         
       div bl
       cmp ah,00h
       je b1 
       inc bl
       loop findDel    
       mov bx,si
b1:    
       mov ax,si
       mov di,bx
       mov si,ax
       jmp cout 

C1:
   mov di,-1     
cout:
    test ax,ax
    js changeSign  
    
initializatian:
    mov     bx,10          
    xor     cx,cx              
    
divide: 
    xor     dx,dx          
    div     bx            ; AX is Quotient, Remainder DX=[0,9]
    push    dx             
    inc     cx             
    test    ax,ax         ;Is quotient zero?
    jnz divide
    
    mov ax,si
    test ax,ax
    js sign
    
print: 
    pop  dx             
    add  dl,"0"         ;Turn into character
    mov  ah,02h         
    int  21h           
    loop  print 
    
    mov ah,02h
    mov dl," "
    int 21h
    mov ah,02h
    mov dl," "
    int 21h
    mov ah,02h
    mov dl," "
    int 21h
    
    mov ax,di
    mov si,di
    
    cmp di,-1
    je exit
    loop c1 
         
    
changeSign:
    mov bx,-1 
    imul bx  
    jmp initializatian
      
sign:
    mov ah,02h
    mov dl,45
    int 21h  
    jmp print

                 
exit:
        mov ax, 4C00h
        int 21h




