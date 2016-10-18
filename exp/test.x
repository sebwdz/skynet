
exp($inputs $outputs)<(
	{inputs $inputs}
	{outputs $outputs}
)>

exps<(
	:exp ((0 0 0)(-1))
	:exp ((0 1 0)(1))
	:exp ((1 0 0)(1))
	:exp ((1 1 0)(-1))
	:exp ((0 0 1)(1))
	:exp ((0 1 1)(1))
	:exp ((1 0 1)(-1))
	:exp ((1 1 1)(1))
)>

tests<(
	:exp ((0 0 0)(-1))
	:exp ((0 0.7 0)(1))
	:exp ((0.7 0 0)(1))
	:exp ((0.7 0.7 0)(-1))
	:exp ((0.7 0.7 0.7)(1))
)>

session($stop $exps $tests)<(
	{stop $stop}
	{exps $exps}
	{tests $tests}
)>

sessions<(
	:session (0.001 :exps :tests)
)>


settings<(
	{type /mlp} [mlp sp]
	
	{inputs 3}
	{layers (3 1)}

	{patern (()(/th)(/th))} [sig th]
)>

main<(
	{settings :settings}
	{sessions :sessions}
	{network :network}
)>

neuron($biais $inputs $type)<(
	{biais $biais}
	{inputs $inputs}
	{type $type}
)>

input($weight $layer $neuron)<(
	{weight $weight}
	{layer $layer}
	{$neuron $neuron}
)>

layer1<(
	:neuron (0.5 0 (:input (0.1 0 0) :input (0.1 0 1))())
	:neuron (0.5 0 (:input (0.1 0 0) :input (0.1 0 1))())
	:neuron (0.5 0 (:input (0.1 0 0) :input (0.1 0 1))())
)>

layer2<(
	:neuron (0.5 0 (
			:input (0.1 1 0) :input (0.1 1 1) :input (0.1 1 2)
	)())
)>

network<(
	{inputs 2}
	{layers (:layer1 :layer2)}
)>