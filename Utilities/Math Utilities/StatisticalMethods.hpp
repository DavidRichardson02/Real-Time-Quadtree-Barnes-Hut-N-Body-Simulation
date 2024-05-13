//  StatisticalMethods.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02
/**
 dev note: if you're wondering wtf this file is, it's simple, basically, I got obsessed with statistical methods for a couple days and now feels like a waste to delete this work so I'm keeping this antiquated shit around cuz i feel like it... exists solely for some obscure(but radical) feature for approximating a reasonable mean from some data manipulation performed on data parsed from user interactions(don't even bother wasting your time thinking about this for more time than you already have, unless your way smarter than me(hardly unlikely), in that case carry on and pardon my procrastination rant
 */

#pragma once
#include "ofConstants.h"






/**
 * @brief Computes a reasonable average of two values.
 *
 * Given two values `max` and `min`, this function first determines the individual orders
 * of magnitude of the values, as well as their magnitude difference. It then uses this
 * information to compute a reasonable average, taking into consideration scenarios where
 * one value is vastly smaller or larger than the other.
 *
 * If the smaller value is as small (in magnitude) as the larger value is large (for example:
 * 10*e-11 and 10*e11), the function returns an average which is the value without the
 * orders of magnitude.
 *
 * @param max The larger of the two numbers.
 * @param min The smaller of the two numbers.
 *
 * @return The computed average.
 */
static inline double ComputeReasonableAverage(double min, double max)
{
	// Calculate orders of magnitude of the individual values.
	double orderOfMagnitudeMax = std::log10(std::abs(max));
	double orderOfMagnitudeMin = std::log10(std::abs(min));
	
	
	// Calculate the difference in orders of magnitude.
	double magnitudeDifference = orderOfMagnitudeMax - orderOfMagnitudeMin;
	
	
	// Dynamic Lp norm calculation
	double p = 1.0 - 0.1 * magnitudeDifference;
	double sum = 0.0;
	sum += std::pow(std::abs(min), p);
	sum += std::pow(std::abs(max), p);
	
	
	double lp_norm_mean = std::pow(sum, 1.0 / p);
	
	
	// Dynamic entropy-based weight
	// Normalizing values for entropy calculation
	double normalized_min = (min - min) / (max - min);
	double normalized_max = (max - min) / (max - min);
	
	// Dynamic entropy-based weight
	double sumEntropy = 0.0;
	
	
	
	
	// Probabilities for entropy calculation
	double total = std::abs(min) + std::abs(max);
	double prob_min = std::abs(min) / total;
	double prob_max = std::abs(max) / total;
	
	if (prob_min > 0)
		sumEntropy += prob_min * std::log(prob_min);
	if (prob_max > 0)
		sumEntropy += prob_max * std::log(prob_max);
	
	
	sumEntropy *= -1;
	
	double weight = 1 / (1 + std::exp(-sumEntropy));
	
	
	
	// Weighted sum of Lp norm mean and arithmetic mean
	double reasonable_mean = weight * lp_norm_mean + (1 - weight) * ((min + max) / 2);
	
	
	return reasonable_mean;
}















/**
 * DetermineSkewness
 * Determines skewness of a distribution with given min, max, and value.
 * Skewness metric is positive for right-skewed and negative for left-skewed data.
 *
 *
 * @param min Minimum value in the range.
 * @param max Maximum value in the range.
 * @param value A value within the range.
 * @return Skewness metric.
 */
static inline double DetermineSkewness(double min, double max, double value)
{
	//
	/*
	 //Compute mean
	 double mean = (min + max + value) / 3.0;
	 
	 //Compute variance and standard deviation
	 double variance = (std::pow(min - mean, 2) + std::pow(max - mean, 2) + std::pow(value - mean, 2)) / 3.0;
	 double std = sqrt(variance);
	 
	 //Compute skewness
	 double skewness = (max - mean) / std - (mean - min) / std;
	 
	 return skewness;
	 //*/
	
	
	///*
	// Determine the median among min, max, and value
	double median;
	
	if ((min <= value && value <= max) || (max <= value && value <= min))
	{
		median = value;
	}
	else if ((value <= min && min <= max) || (max <= min && min <= value))
	{
		median = min;
	}
	else
	{
		median = max;
	}
	
	// Compute the distances from the median
	double dist_min = median - min;
	double dist_max = max - median;
	
	// Skewness metric, which is positive for right-skewed and negative for left-skewed
	double skewness = dist_max - dist_min;
	
	return skewness;
	//*/
}








/**
 * Huber's M-estimator for a robust estimation of central tendency.
 *
 * Huber's M-estimator is a generalization of the mean that is less sensitive to outliers.
 * For values close to zero, it behaves linearly, like the mean. For values far from zero,
 * it becomes a constant function, resembling the median. This makes it robust against outliers.
 * Huber's M-estimator reduces the impact of outliers by transitioning from a quadratic function
 * for small residuals to a linear function for large residuals.
 *
 *
 *
 * For |x| <= delta, it's linear (like the mean), and for |x| > delta, it's constant (like the median).
 *
 * @param x Value at which the Huber's M-estimator is computed.
 * @param delta Threshold for the Huber function, controlling the robustness.
 * @return Value of the Huber's M-estimator at x.
 */
static inline double HuberMEstimator(double x, double delta)
{
	// If |x| is within delta, act linearly.
	// Otherwise, become a constant function.
	return std::abs(x) <= delta ? x : delta * std::copysign(1.0, x);
}






/**
 * The Huber function can be generalized by allowing the parameter delta to vary.
 * Provides robustness against outliers, where smaller values of delta will reduce the influence of outliers.
 *
 * @param x The input value.
 * @param delta Threshold controlling sensitivity.
 * @return The generalized M-estimator value at x.
 */
static inline double Generalized_HuberMEstimator(double x, double delta)
{
	return (x*x / (2.0 * delta)) * (std::abs(x) <= delta) + (std::abs(x) - delta/2.0) * (std::abs(x) > delta);
}






/**
 * Gaussian Likelihood.
 *
 * Computes the likelihood value for a Gaussian distribution with given mean and standard deviation.
 *
 * @param x Value at which the likelihood is computed.
 * @param mu Mean of the Gaussian distribution.
 * @param sigma Standard deviation of the Gaussian distribution.
 * @return Likelihood value at x.
 */
static inline double GaussianLikelihood(double x, double mu, double sigma)
{
	return (1.0 / (sigma * sqrt(2 * M_PI))) * exp(-0.5 * std::pow((x - mu) / sigma, 2));
}






/**
 * ComputeReasonableMean
 *
 * Reasonable Mean Computation.
 * This function combines several statistical methods to compute a mean value
 * that considers both the magnitude difference between two numbers and their
 * individual entropy. The method uses Huber's M-estimator for robustness against
 * outliers and skewed distributions, entropy for adaptive weighting, and Bayesian updating to
 * derive a posterior estimate.
 *
 *
 *
 ----- Bayesian Updating -----
 * In Bayesian statistics, the posterior distribution is proportional to the product of the likelihood and the prior.
 * Here, the likelihood represents our belief about the data given certain parameters, and the prior represents
 * our initial belief about those parameters before observing any data. After observing the data,
 * these two beliefs are combined to form a posterior belief about the parameters.
 *
 *
 *
 ----- Likelihood Formulations -----
 * Lp Norm Likelihood: The first likelihood is based on the Lp norm of the data, where the parameter 'p' is determined by the magnitude
 * difference between the min and max values. Assumed a Gaussian distribution centered at this mean, with a variance inversely
 * proportional to the entropy weight. The choice of Gaussian here can be interpreted as the "most uninformed" choice under maximum
 * entropy principles.
 *
 * Huber M-estimator Likelihood: The second likelihood is based on Huber's M-estimator, which provides a robust estimate of the mean.
 * Again, assumed a Gaussian distribution but with a variance controlled by 'δ', the Huber parameter.
 *
 *
 *
 ----- Entropy Weighting -----
 * Entropy is used as an uncertainty measure. In this context, it helps adjust the variance of the likelihood based on the Lp norm mean.
 * A lower entropy would indicate higher certainty and therefore lower variance, and vice versa.
 *
 *
 *
 ----- Posterior Computation -----
 * Use the product of Gaussians formula to combine these different sources of evidence. This formula is an analytical
 * solution for the posterior when all the involved distributions are Gaussian. The posterior mean is a weighted sum of all
 * the different 'mean' estimates, where the weights are determined by the variances of these estimates. Lower variance would imply
 * higher confidence and thus higher weight in this sum.
 *
 *
 * Step-by-step analysis of the ComputeReasonableMean function’s execution is provided in function implementation in 7 steps.
 *
 * @param min The minimum value.
 * @param max The maximum value.
 * @param delta Threshold for the Huber function, controlling the robustness.
 * @return The Bayesian "reasonable" mean.
 */
static inline double ComputeReasonableMean(double min, double max, double value)
{
	// 1. Calculate the order of magnitude of `min` and `max`
	double order_min = std::log10(std::abs(min));
	double order_max = std::log10(std::abs(max));
	double magnitudeDifference = order_max - order_min;
	
	
	
	
	// 2. Determine skewness-based delta for generalized Huber estimator.
	double delta = DetermineSkewness(min, max, value);
	
	
	
	
	// 3. Calculate the Lp norm mean using the generalized Huber's estimator. The value of `p` is determined by the magnitude difference between `min` and `max`.
	double p = 1.0 - 0.1 * magnitudeDifference;
	double sum = std::pow(Generalized_HuberMEstimator(min, delta), p) + std::pow(Generalized_HuberMEstimator(max, delta), p);
	double lp_norm_mean = std::pow(sum, 1.0 / p);
	
	
	
	
	// 4. Compute entropy weight for Bayesian update. The probabilities used for entropy calculation are computed based on the generalized Huber's estimator of `min`, `max`, and `value`.
	//For the entropy-based approach: We'll use a Gaussian likelihood centered at the Lp norm mean with variance inversely proportional to the entropy.
	//For the M-estimator approach: Gaussian likelihood centered at the Huber mean with variance determined by delta.
	double total = std::abs(Generalized_HuberMEstimator(min, delta)) + std::abs(Generalized_HuberMEstimator(max, delta)) + std::abs(Generalized_HuberMEstimator(value, delta));
	double prob_min = std::abs(Generalized_HuberMEstimator(min, delta)) / total;
	double prob_max = std::abs(Generalized_HuberMEstimator(max, delta)) / total;
	
	double sumEntropy = 0.0;
	if (prob_min > 0) sumEntropy += prob_min * std::log(prob_min);
	if (prob_max > 0) sumEntropy += prob_max * std::log(prob_max);
	sumEntropy *= -1;
	double entropy_weight = 1 / (1 + std::exp(-sumEntropy));
	
	
	
	
	//  5. Define the prior mean and variance for Bayesian update.
	// The prior mean is simply the average of `min` and `max`, and the prior variance is set to a large value to indicate low confidence in the prior.
	double prior_mean = (min + max) / 2.0;
	double prior_variance = 1000.0; // Arbitrarily large number indicating low confidence in prior
	
	
	
	
	// 6. Define two likelihoods:
	// - The first likelihood is a Gaussian distribution centered at the Lp norm mean with variance inversely proportional to the entropy weight.
	// - The second likelihood is a Gaussian distribution centered at the Huber mean with variance determined by delta.
	double likelihood1_mean = lp_norm_mean;
	double likelihood1_variance = 1.0 / (entropy_weight + 1e-5);  // Added a small constant to prevent division by zero
	
	double likelihood2_mean = (Generalized_HuberMEstimator(min, delta) + Generalized_HuberMEstimator(max, delta)) / 2;
	double likelihood2_variance = delta;
	
	
	
	
	//  7. Compute the Bayesian "reasonable" mean.
	// This is the mean of the posterior distribution, which is proportional to the product of the prior and the two likelihoods.
	// Proportional to the product of the prior and the two likelihoods. We'll then derive a Bayesian "reasonable mean" as the mean of this posterior.
	double posterior_mean = (likelihood1_mean / likelihood1_variance + likelihood2_mean / likelihood2_variance + prior_mean / prior_variance) /
	(1.0 / likelihood1_variance + 1.0 / likelihood2_variance + 1.0 / prior_variance);
	double posterior_variance = 1.0 / (1.0 / likelihood1_variance + 1.0 / likelihood2_variance + 1.0 / prior_variance);
	
	
	std::cout << "\n\n\n\n\nposterior_mean: " << posterior_mean;
	std::cout << "\nposterior_variance: (" << posterior_variance;
	
	
	
	return posterior_mean; // Bayesian "reasonable" mean
}
