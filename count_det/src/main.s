.text
.global count_det

count_det:
        push {r1-r10}

        ldr r1, [r0]
        ldr r2, [r0, #4]
        ldr r3, [r0, #8]
        ldr r4, [r0, #12]
        ldr r5, [r0, #16]
        ldr r6, [r0, #20]
        ldr r7, [r0, #24]
        ldr r8, [r0, #28]
        ldr r9, [r0, #32]

        mul r0, r1, r5
        mul r0, r9

        mul r10, r2, r6
        mul r10, r7
        add r0, r10

        mul r10, r3, r4
        mul r10, r8
        add r0, r10

        mul r1, r6
        mul r1, r8
        sub r0, r1

        mul r2, r4
        mul r2, r9
        sub r0, r2

        mul r3, r5
        mul r3, r7
        sub r0, r3

        pop {r1-r10}
        bx lr
