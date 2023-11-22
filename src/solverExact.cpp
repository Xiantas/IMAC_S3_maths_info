

// dans le main ça après
Eigen :: JacobiSVD < Eigen :: MatrixXd > svd (A,Eigen :: ComputeThinU | Eigen :: ComputeFullV );
Eigen :: VectorXd x = svd . matrixV (). rightCols (1);

Eigen::MatrixXd solveExact(std::vector<Eigen::VectorXd> &truc) {
  assert(truc.size()  == 5);
  

}