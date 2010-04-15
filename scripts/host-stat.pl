#!/usr/bin/perl
#

use strict;
use warnings;

my %stat_hash;

while (<>) {
    chomp;
    my ($url, $status) = split /\t/;

    my $host;
    if ($url =~ /^https?:\/\/([\w\-\.]+(?::\d+)?)(?:\/|$)/) {
        $host = $1;
    } else {
        warn "can not get host from url: $url\n";
        next;
    }

    my $key = "$host\t$status";
    if (exists $stat_hash{$key}) {
        $stat_hash{$key} ++;
    } else {
        $stat_hash{$key} = 1;
    }
}


while (my ($k, $v) = each %stat_hash) {
    print "$k\t$v\n" if $v > 100;
}
