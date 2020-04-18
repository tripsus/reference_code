#
# Wrap the builtin cd command to maintain directory history.
#
function cd --description "Change directory"
    set -l MAX_DIR_HIST 25
    set -l cd_status = 1
    if test (count $argv) -gt 1
        printf "%s\n" (_ "Too many args for cd command")
        return 1
    end
 
    if test "$argv" = "l"
        set -l count 0
        for val in $dirprev
            set count (math $count + 1)
            echo "$count: $val"
        end
        return 1
    end

    # Skip history in subshells.
    if status --is-command-substitution
        builtin cd $argv
        return $status
    end

    # Avoid set completions.
    set -l previous $PWD
    set -l CD_PATH_HISTORY $PWD
    if test "$argv" = "-"
        if test "$__fish_cd_direction" = "next"
            nextd
        else
            prevd
        end
        return $status
    end
    # is_integer_input 1 is string and 0 is integer
    
    set -l is_integer_input 0
    if string match -qr '^[0-9]|[0-9][0-9]$' -- $argv[1]
        #echo "Integer matched"
        if test (count $dirprev) -lt $argv
            printf "%s\n" (_ "Previous directory stack is less than passed input")
            return 1
        end
        set -x is_integer_input 1
    end
    
    if test $is_integer_input -eq 1
        cd $dirprev[$argv]
    else
        builtin cd $argv
    end
    set -x cd_status $status 
    #echo $is_integer_input
    #echo $cd_status
    if test "$cd_status" = "0" -a "$is_integer_input" = 1
        #echo "integer input" 
        set -q dirprev[$MAX_DIR_HIST]
        and set -e dirprev[$argv]
        set -e dirprev[$argv]
        #set -g dirprev $dirprev $previous
        set -e dirnext
        set -g __fish_cd_direction prev
    end
    if test $cd_status -eq 0 -a "$PWD" != "$previous" -a "$is_integer_input" = 0
        set -q dirprev[$MAX_DIR_HIST]
        and set -e dirprev[1]
        set -g dirprev $dirprev $previous
        set -e dirnext
        set -g __fish_cd_direction prev
        end
    return $cd_status
end

