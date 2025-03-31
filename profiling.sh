sudo perf record -F 999 -a -g -- ./build/challenges/challenge.out && \
	sudo perf script > out.perf && \
	../FlameGraph/stackcollapse-perf.pl out.perf > out.folded && \
	../FlameGraph/flamegraph.pl out.folded > kernel.svg && \
	google-chrome ./kernel.svg

