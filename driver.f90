program driver
integer :: NDIM

! Declare variables for the clock and final value
real (kind=8) :: wall_start, wall_end
real (kind=8) :: cpu_start, cpu_end
real (kind=8) :: trace

! Declare outside functions that will be used
integer :: startval, stopval, stepval, nthreads
real (kind=8) :: walltime
real (kind=8) :: cputime 
real (kind=8) :: dot 
external walltime, cputime, dot

character (len=8) :: carg1, carg2, carg3, carg4

! Make variables for vectors and matrices
real (kind=8), dimension(:), allocatable :: veca, vecb, vecx
real (kind=8), dimension(:,:), allocatable :: matrixa, matrixb, matrixc

! get command line arguments into variables
! 1 is start, 2 is stop, 3 is step, and 4 is number of threads

call get_command_argument(1, carg1)
call get_command_argument(2, carg2)
call get_command_argument(3, carg3)
call get_command_argument(4, carg4)

! Use Fortran internal files to convert command line arguments to ints

read (carg1,'(i8)') startval
read (carg2,'(i8)') stopval
read (carg3,'(i8)') stepval
read (carg4,'(i8)') nthreads 

#if defined(ILSDRIVER)
print *, "RUNNING ITERATIVE LINEAR SOLVER"

#elif defined(DLSDRIVER)
print *, "RUNNING DIRECT LINEAR SOLVER"

#elif defined(VVMDRIVER)
print *, "RUNNING TENSOR PRODUCT"

#elif defined(MVVDRIVER)
print *, "RUNNING MATRIX VECTOR MULTIPLICATION"

#elif defined(MMMDRIVER)
print *, "RUNNING MATRIX MATRIX MULTIPLICATION"

! Dot Product is Default Test
#else
print *, "RUNNING DOT PRODUCT"
#endif

do iter = startval, stopval, stepval
 

NDIM = iter

! Allocate memory to the vectors 
allocate ( veca(NDIM), stat=ierr)
allocate ( vecb(NDIM), stat=ierr)
allocate ( vecx(NDIM), stat=ierr)
allocate ( matrixa(NDIM,NDIM), stat=ierr)
allocate ( matrixb(NDIM,NDIM), stat=ierr)
allocate ( matrixc(NDIM,NDIM), stat=ierr)

! Fill Vectors A and B
do i = 1, NDIM 
  veca(i) = sqrt(dble(NDIM)) 
  vecb(i) = 1.0 / sqrt( dble(NDIM))
enddo

! Zero Matrices
matrixa = 0.0
matrixb = 0.0
matrixc = 0.0

#if defined(DLSDRIVER) || defined(ILSDRIVER)
call buildLinearSystem(NDIM, matrixa, vecb, vecx)
#else
call vvm(nthreads, NDIM, veca, vecb, matrixa)
call vvm(nthreads, NDIM, veca, vecb, matrixb)
#endif

! Start the clock
wall_start = walltime()
cpu_start = cputime()
trace = 0.0

! Directives to run the functions except for DOT
#if defined(ILSDRIVER)
call ils(nthreads, NDIM, matrixa, vecb, vecx)

#elif defined(DLSDRIVER)
call dls(nthreads, NDIM, matrixa, vecb, vecx)

#elif defined(VVMDRIVER)
call vvm(nthreads, NDIM, veca, vecb, matrixc)

#elif defined(MVVDRIVER)
call mvv(nthreads, NDIM, matrixa, veca, vecx)

#elif defined(MMMDRIVER)
call mmm(nthreads, NDIM, matrixa, matrixb, matrixc)

! Dot Product is Default Test
#else
trace = dot(nthreads, NDIM, veca, vecb)
#endif

! End clock time
cpu_end = cputime()
wall_end = walltime()

! Directives for the trace values of each function
#if defined(DLSDRIVER) || defined(ILSDRIVER) || defined(MVVDRIVER)
trace = 0.0
do i=1, NDIM
   trace = max(trace, abs(vecx(i)-dble(i)))
enddo
#elif defined(MMMDRIVER) || defined(VVMDRIVER)
trace = 0.0
do i=1, NDIM 
    trace = trace + matrixc(i,i)
enddo
#endif

! Calculate Megaflops
mflops = 2*dble(NDIM)/ (cpu_end-cpu_start) / 1.0e6
mflops2 = 2*dble(NDIM)/ (wall_end-wall_start)/ 1.0e6

! print out final information
print *, NDIM, trace, cpu_end-cpu_start, wall_end-wall_start, mflops, mflops2


deallocate(matrixa)
deallocate(matrixb)
deallocate(matrixc)
deallocate(veca)
deallocate(vecb)
deallocate(vecx)

enddo
end program driver

! Subroutine to build random linear systems for linear solvers to used
! Written by Dr. Andrew Pounds
subroutine buildLinearSystem(N, A, B, X)
integer :: N;
real (kind=8), dimension(N,N) :: A 
real (kind=8), dimension(N) :: B, X
real (kind=8) :: rowsum

call init_random_seed()
call random_number(A)

do i =1, N
  X(i) = dble(i)
enddo

B = matmul(X,A)
end subroutine

! Needed for random number generator; written by Dr. Andrew Pounds
SUBROUTINE init_random_seed() 
  INTEGER :: i, n, clock 
  INTEGER, DIMENSION(:), ALLOCATABLE :: seed 
 
  CALL RANDOM_SEED(size = n) 
  ALLOCATE(seed(n)) 
 
  CALL SYSTEM_CLOCK(COUNT=clock) 

  seed = clock + 37 * (/ (i - 1, i = 1, n) /)
  CALL RANDOM_SEED(PUT = seed)

  DEALLOCATE(seed)
END SUBROUTINE