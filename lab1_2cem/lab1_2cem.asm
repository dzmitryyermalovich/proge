.model small
.stack 256

.data  

N dw 4
inputs dw 1, 2, 3, 4
array dw 1, 10, 100
numberSign dw 0 
index dw 0              
.code   
        mov ax,@data
        mov ds,ax
        
EnterNumbers:
            lea bx,numberSign 
            mov [bx+0],0
            
            mov cx, 3     
            mov di,0x0D
             
    inpt:   mov ah, 08h
            int 21h
            mov ah,0
            
            cmp al,0x2D
            je negat
            
            cmp di,ax
            je body
               
            mov si,ax
            push si
            loop inpt
            jmp body
            
    negat:  
            lea bx,numberSign
            mov [bx+0],99
            jmp inpt        
            
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
            
            lea bx,numberSign
            cmp [bx+0],99
            je changeNumberSign
            
            jmp saveNumber
            
    changeNumberSign:
            mov dx,-1
            imul dx
            mov si,ax
            jmp saveNumber
            
    saveNumber:
    
            lea bx,index
            mov si,[bx+0]
            lea bx,inputs
            mov [bx+si],ax
            
            lea bx,index
            add [bx+0],2
            
            cmp [bx+0],8
            je wholeCode
            jmp EnterNumbers
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 

wholeCode:
    
    lea si,inputs
        
    mov ax,[si+0]
    mov cx,[si+4]    
    
    imul cx  
    
    mov cx,ax
    
    mov bx,[si+2]
    mov dx,[si+6]
    
    sub bx,dx
    
    cmp cx,bx
    jne firstCondition
    
    mov ax,[si+0] 
    mov dx,[si+6] 
    
    cmp ax,dx
    jg firstCondition

    mov bx,[si+2]
    mov cx,[si+4]
    sub bx,cx
    
    mov ax,[si+0]
    mov dx,[si+6]
    add ax,dx
    
    cmp bx,ax
    jle secondCondition 
    
    mov ax,[si+0]
    mov bx,[si+2]
    cmp ax,bx
    jge secondCondition
    
    mov ax,[si+2]
    imul ax
    mov dx,[si+6]
    mov cx,[si+4]
    sub ax,dx
    add ax,[si+4]
    mov si,ax
    jmp cout
       
secondCondition:
    lea si,inputs
    
    mov cx,[si+4]
    mov ax,2
    imul cx
    mov cx,ax
    mov ax,3
    mov dx,[si+6]
    imul dx
    add cx,ax
    mov ax,-5
    add cx,ax
    mov ax,cx
    mov si,ax
    jmp cout
        
firstCondition:
    lea si,inputs
    
    mov cx,[si+4]
    mov dx,[si+6]
    add cx,dx
    mov ax,cx
    mov bx,[si+2]
    imul bx
    mov bx,ax
    mov ax,[si+0]
    sub ax,bx  
     
    mov si,ax  ;!!! ax,si contain answer
    jmp cout


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  

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
    jmp exit     
    
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
    mov ax, 00h
    mov al, 0
    int 21h




