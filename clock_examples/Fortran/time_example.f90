program timing_example
!--------------------------------------------------
! Example of using a timer wrapper in Fortran 2008
!--------------------------------------------------
    use iso_fortran_env, only: real64, stdout => output_unit
    implicit none
    integer           :: sleepy_time = 1
    real(kind=real64) :: time1, time2
    real(kind=real64), external ::  elapsedtime

    time1 = elapsedtime()
    call sleep(sleepy_time)
    time2 = elapsedtime() - time1

    ! The printed time should be only slightly larger than the value of sleepy_time
    write(stdout,666) 'Elapsed time = ', time2, ' seconds'
    666 format(a, es25.17, a)

end program timing_example
