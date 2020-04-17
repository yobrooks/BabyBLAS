program dotdriver 

integer :: NDIM

real (kind=8) :: wall_start, wall_end
real (kind=8) :: cpu_start, cpu_end
real (kind=8) :: trace


integer :: startval, stopval, stepval
real (kind=8) :: walltime
real (kind=8) :: cputime 
real (kind=8) :: dot 
external walltime, cputime, dot

character (len=8) :: carg1, carg2, carg3

real (kind=8), dimension(:), allocatable :: veca, vecb
real (kind=8), dimension(:,:), allocatable :: matrixa, matrixb, matrixc

!modified to use command line arguments

call get_command_argument(1, carg1)
call get_command_argument(2, carg2)
call get_command_argument(3, carg3)

! Use Fortran internal files to convert command line arguments to ints

read (carg1,'(i8)') startval
read (carg2,'(i8)') stopval
read (carg3,'(i8)') stepval
 
do iter = startval, stopval, stepval
  

NDIM = iter

allocate ( veca(NDIM), stat=ierr)
allocate ( vecb(NDIM), stat=ierr)


do i = 1, NDIM 
    veca(i) = sqrt(dble(NDIM)) 
    vecb(i) = 1.0 / sqrt( dble(NDIM))
enddo

wall_start = walltime()
cpu_start = cputime()

trace = dot(1, NDIM, veca, vecb)

cpu_end = cputime()
wall_end = walltime()

mflops= 2*dble(NDIM)/ (cpu_end-cpu_start) / 1.0e6
mflops2 = 2*dble(NDIM)/ (wall_end-wall_start)/ 1.0e6

print *, NDIM, trace, cpu_end-cpu_start, wall_end-wall_start,mflops, mflops2


deallocate(veca)
deallocate(vecb)

enddo

end program dotdriver 