function elapsedtime() result (timing)
!------------------------------------------------------------------------------------------
! Fortran has three different language-specified timers. This function returns a
! double precision number, the number of seconds since some unspecified event.
!
! Use the "version" variable to choose among the variants.
!
! Warnings: the system clock version does not check against overflow in the counter.
! Add the argument count_max for that if you need it. The date and time version is
! more robust, but won't work across monthly boundaries. So a start time on 31 Aug
! and a finish time on 2 September won't work.
!------------------------------------------------------------------------------------------
    use iso_fortran_env, only: real64, int64, stderr => error_unit
    implicit none
    real(kind=real64)   :: timing
    real                :: cpuclock
    integer             :: time_array(8)
    integer(kind=int64) :: clockcount, count_rate

    character(len=15)   :: version

    !---------------------------------------------------------------------------
    ! Pick one of the three below. This could also be made an optional argument 
    ! to this function, but why bother?
    !---------------------------------------------------------------------------
    ! version = 'date_and_time'
    ! version = 'cpu_time'
    version = 'system_clock'

    select case (adjustl(version))

    ! Option 1
    case ("date_and_time")
        call date_and_time (values=time_array)
        timing =  time_array(8) * (1.0d-3)     &   ! number of milliseconds
                + time_array(7) * (1.0d0)      &   ! number of seconds
                + time_array(6) * (6.0d1)      &   ! number of minutes
                + time_array(5) * (3.6d3)      &   ! number of hours
                + time_array(3) * (24*3.6d3)       ! number of days

    ! Option 2
    case ("system_clock")
        call system_clock(clockcount, count_rate)
        timing = real(clockcount,kind=real64)/real(count_rate,kind=real64)

    ! Option 3
    case ("cpu_time")
        call cpu_time(cpuclock)
        timing = cpuclock

    ! Non-option
    case default
        timing = -17.0
        write(stderr,*) 'WHAT were you thinking?'

    end select

    return

end function elapsedtime
