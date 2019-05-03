DwarfElephant
=====

"Fork DwarfElephant" to create a new MOOSE-based application.

For more information see: [http://mooseframework.org/create-an-app/](http://mooseframework.org/create-an-app/)

The Reduced Basis Method
------------------------


The RB method has been also implemented within the MOOSE framework. Our implementation is primarily based on the rbOOmit package provided by libMesh. Although we are using the RB method for approximating the FE space, the method in general is independent of the discretisation scheme. In the following, we consider a problem of the form (\ref{PDE}) for explaining the background theory \cite{prud'homme2002, hesthaven2016}:

\begin{equation}
a(u(\mu),v;\mu)=f(v;\mu), \qquad	\forall v \in X,
\label{PDE}
\end{equation}
%
where $a$ is an affine parametric bilinear form, and $f$, $l$ are affine parametric linear forms on $X$. We need to find $u(\mu) \in X$ such that for a given $\mu \in \mathcal{D}$ the equation above is satisfied and afterwards we evaluate (\ref{PDE LHS}) \cite{prud'homme2002, hesthaven2016}:
%
\begin{equation}
s(\mu)=l(u(\mu);\mu).
\label{PDE LHS}
\end{equation}
%
All linear and bilinear forms used for this project are affine parameter-dependent. Hence, they are decomposable in a parameter-dependent and a parameter-independent part. For the compliant case, which we are going to consider,  $f$, $l$, and $a$ are continuous on $X$. Furthermore, $a$ is symmetric and parametrically coercive.
As previously mentioned, the principal idea of the RB approach is the decomposition into an offline-online procedure. For the construction of the low-order approximations, we have to take snapshots and combine them in the most ``clever" way. Of course, the question remains which algorithm is most suitable. In case of the RB method we use a Greedy algorithm to full-fill this task. Performing the Greedy algorithm involves the following steps \cite{prud'homme2002, hesthaven2016},
%
\begin{flalign*}
& \mathrm{while}\ \Delta_{N-1}^{max} \geq \epsilon_{tol,min} &\\
& \quad N=N+1; &\\
& \quad \mu_N^* = \arg \max_{\mu \in \Xi_{train}} \Delta_{N-1}(\mu) &\\
& \quad S_N=S_{N-1}\cup \mu_N^* &\\
& \quad X_N=X_{N-1}+\mathrm{span}\lbrace u^\mathcal{N}(\mu_N^*)\rbrace & \\
& \mathrm{end}
\end{flalign*}
% 

