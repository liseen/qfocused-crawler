#!/usr/bin/env perl

use strict;
use warnings;

use TokyoTyrant;

my $url = shift || 'http://travel.sina.com.cn/';

# create the object
my $rdb = TokyoTyrant::RDBTBL->new();

# connect to the server
if(!$rdb->open("localhost", 1978)){
    my $ecode = $rdb->ecode();
    printf STDERR ("open error: %s\n", $rdb->errmsg($ecode));
}

# search for records
my $qry = TokyoTyrant::RDBQRY->new($rdb);

# a empty string means the primary key
#$qry->addcond("", $qry->QCSTREQ, $url);
my $res = $qry->search();
foreach my $rkey (@$res){
    my $rcols = $rdb->get($rkey);
    while (my ($k, $v) = each %$rcols) {
        print "##$k:\n$v\n";
    }
}

# close the connection
if(!$rdb->close()){
    my $ecode = $rdb->ecode();
    printf STDERR ("close error: %s\n", $rdb->errmsg($ecode));
}

__END__
# store a record
my $pkey = $rdb->genuid();
my $cols = { "name" => "mikio", "age" => "30", "lang" => "ja,en,c" };
if(!$rdb->put($pkey, $cols)){
    my $ecode = $rdb->ecode();
    printf STDERR ("put error: %s\n", $rdb->errmsg($ecode));
}

# store another record
$cols = { "name" => "falcon", "age" => "31", "lang" => "ja", "skill" => "cook,blog" };
if(!$rdb->put("x12345", $cols)){
    my $ecode = $rdb->ecode();
    printf STDERR ("put error: %s\n", $rdb->errmsg($ecode));
}

 # search for records
 my $qry = TokyoTyrant::RDBQRY->new($rdb);
 $qry->addcond("age", $qry->QCNUMGE, "20");
 $qry->addcond("lang", $qry->QCSTROR, "ja,en");
 $qry->setorder("name", $qry->QOSTRASC);
 $qry->setlimit(10);
 my $res = $qry->search();
 foreach my $rkey (@$res){
     my $rcols = $rdb->get($rkey);
     printf("name:%s\n", $rcols->{name});
 }
 
 # close the connection
 if(!$rdb->close()){
     my $ecode = $rdb->ecode();
     printf STDERR ("close error: %s\n", $rdb->errmsg($ecode));
 }
