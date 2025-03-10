
i=1000
testsFolder=./tests2/

rm -f failed.cmd
rm -f success.cmd
for cmd in $testsFolder*.command; do
	if [[ -f $cmd ]]; then
		out=${cmd%.command}.out;
		in=${cmd%.command}.in;
		bash $cmd > tmp
		#tail -n 1 tmp > _tmp;
		#mv _tmp tmp
		if ! diff -q tmp $out; then
			head -n 1 $cmd >> failed.cmd
			echo >> failed.cmd
		else
			head -n 1 $cmd >> success.cmd
			echo >> success.cmd
		fi

		((i--));
		if [[ $i -le 0 ]]; then
			break;
		fi
	fi
done
