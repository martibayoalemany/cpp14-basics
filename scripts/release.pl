#!/usr/bin/env perl
use Cwd 'abs_path';

my $name="cpp14-basics";
my $script_path = abs_path($0);
$script_path =~s#([^/]+)$##;
my $source=$script_path."..";
my $target_dir=$script_path."../../release";

my $script=<<EOF;
mkdir -p ${target_dir}/$name
cd ${target_dir}/$name
git clone $source .
cd ..
tar cvfz "${target_dir}/${name}.tar.gz" $name
gpg --armor --output ${name}.tar.gz.sig --detach-sign ${name}.tar.gz
gpg --verify ${name}.tar.gz.sig ${name}.tar.gz
sha1sum ${name}.tar.gz > ${name}.tar.gz.sha1
tar cvfz ${target_dir}/${name}_release.tar.gz  ${name}.tar.gz.sig ${name}.tar.gz ${name}.tar.gz.sha1
rm -rf ${target_dir}/$name
rm ${name}.tar.gz.sig ${name}.tar.gz ${name}.tar.gz.sha1
EOF

system ($script);

print "\n".$source."\n";
print $tmp_dir."\n";
print $target_dir."\n";
system(`which nautilus` ${target_dir});



