# SpellingCorrector
a c++ code of spelling corrector
单词校正器,主要原理是依据贝叶斯原理P(C|W) = P(C)*P(W|C)/P(W)。
详情见http://norvig.com/spell-correct.html      
。算法步骤为求编辑距离小的单词，
如果存在，求频率最大的单词为正确单词，如果没有则编辑距离+1....如果编辑距离
为2依然没有，那就认为输入的单词为新词，是正确的
本程序是本人匆忙之下写的，没有做任何优化，所以效率方面存在不足，而且本程序
算法也有有待改进的地方，所以大家将就着看吧*/
