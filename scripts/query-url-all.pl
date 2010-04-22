#!/usr/bin/env perl

use strict;
use warnings;

use TokyoTyrant;

# create the object
my $rdb = TokyoTyrant::RDB->new();

# connect to the server
if(!$rdb->open("localhost", 1979)){
    my $ecode = $rdb->ecode();
    printf STDERR ("open error: %s\n", $rdb->errmsg($ecode));
}

# traverse records
$rdb->iterinit();
while(defined(my $key = $rdb->iternext())){
    my $value = $rdb->get($key);
    #if(defined($value)) {
    #    printf("%s\t%s\n", $key, $value);
    #}
    if ($value eq '1') {
        print $key . "\n";
    }
}


