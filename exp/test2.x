
exp($inputs $outputs)<(
	{outputs $outputs}
	{inputs $inputs}
)>

exps<(
	:exp ((
			0.02368064953 0.7232746955 0.9458728011 1 0.5649526387
			0.004059539919 0.7131258457 0.4851150203 0.3416779432 0
	)(0 1))
	:exp ((
			0 0.06176203451 0.4105358765 0.8374205268 0.7002724796
			0.7638510445 0.7638510445 0.6194368756 0.8955495005 1
	)(0 1))
)>

session($stop $exps $tests)<(
	{exps $exps}
	{tests $tests}
	{stop $stop}
)>

sessions<(
	:session (0.05 :exps 0 ())
)>

settings<(
	{type /mlp}
	{inputs 10}
	{layers (10 2)}
)>

main<(
	{settings :settings}
	{sessions :sessions}
)>