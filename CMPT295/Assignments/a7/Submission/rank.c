
void compute_ranks(float *F, int N, int *R, float *avg, float *passing_avg, int *num_passed) {
    int i, j;
    int temp_num_passed = 0;				// use a local variable to avoid num_passed, 
    float temp_avg = 0.0;					// passing_avg, avg, and everyone's grade everytime 
    float temp_passing_avg = 0.0;			// when use
    float grade1, grade2, grade3, grade4;	//
    float current_index = 0.0;
    int unrolledN = (N/4)*4;

    for(i = 0; i<N;i++){
    	R[i] = 1;
    }

    // unroll the loop of index i (to determin rank for each student)into 4 steps
    // the unrolling reduce the cost of memory access and number of loop to calculate the total
    // result. As I choose to unrolling by 4, and unrolling the loop contained in the loop by 4
    // as well, the whole can be ideally 16 times faster.
    for (i = 0; i < unrolledN; i+=4) {
        grade1 = F[i];
        grade2 = F[i+1];
        grade3 = F[i+2];
        grade4 = F[i+3];
        //unroll the loop of index j(to check with every other student's grade) into 4 steps
		for (j = i+1; j < unrolledN; j+=4){

			if(j == i+1){

				float cmp_grade1 = F[j];
				if(grade1 < cmp_grade1){
					R[i] ++;
				} else if(grade1 > cmp_grade1){
					R[j] ++;
				}

				float cmp_grade2 = F[j+1];
				if(grade1 < cmp_grade2){
					R[i] ++;
				} else if (grade1 > cmp_grade2){
					R[j+1] ++;
				}
				if(grade2 < cmp_grade2){
					R[i+1] ++;
				} else if (grade2 > cmp_grade2){
					R[j+1] ++;
				}

				float cmp_grade3 = F[j+2];
				if(grade1 < cmp_grade3){
					R[i] ++;
				} else if (grade1 > cmp_grade3){
					R[j+2] ++;
				}
				if(grade2 < cmp_grade3){
					R[i+1] ++;
				} else if (grade2 > cmp_grade3){
					R[j+2] ++;
				}
				if(grade3 < cmp_grade3){
					R[i+2] ++;
				} else if (grade3 > cmp_grade3){
					R[j+2] ++;
				}

				float cmp_grade4 = F[j+3];
				if(grade1 < cmp_grade4){
					R[i] ++;
				} else if (grade1 > cmp_grade4){
					R[j+3] ++;
				}
				if(grade2 < cmp_grade4){
					R[i+1] ++;
				} else if (grade2 > cmp_grade4){
					R[j+3] ++;
				}
				if(grade3 < cmp_grade4){
					R[i+2] ++;
				} else if (grade3 > cmp_grade4){
					R[j+3] ++;
				}
				if(grade4 < cmp_grade4){
					R[i+3] ++;
				} else if (grade4 > cmp_grade4){
					R[j+3] ++;
				}

			} else {
				float cmp_grade1 = F[j];
				if(grade1 < cmp_grade1){
					R[i] ++;
				} else if (grade1 > cmp_grade1){
					R[j] ++;
				}
				if(grade2 < cmp_grade1){
					R[i+1] ++;
				} else if (grade2 > cmp_grade1){
					R[j] ++;
				}
				if(grade3 < cmp_grade1){
					R[i+2] ++;
				} else if (grade3 > cmp_grade1){
					R[j] ++;
				}
				if(grade4 < cmp_grade1){
					R[i+3] ++;
				} else if (grade4 > cmp_grade1){
					R[j] ++;
				}

				float cmp_grade2 = F[j+1];
				if(grade1 < cmp_grade2){
					R[i] ++;
				} else if (grade1 > cmp_grade2){
					R[j+1] ++;
				}
				if(grade2 < cmp_grade2){
					R[i+1] ++;
				} else if (grade2 > cmp_grade2){
					R[j+1] ++;
				}
				if(grade3 < cmp_grade2){
					R[i+2] ++;
				} else if (grade3 > cmp_grade2){
					R[j+1] ++;
				}
				if(grade4 < cmp_grade2){
					R[i+3] ++;
				} else if (grade4 > cmp_grade2){
					R[j+1] ++;
				}

				float cmp_grade3 = F[j+2];
				if(grade1 < cmp_grade3){
					R[i] ++;
				} else if (grade1 > cmp_grade3){
					R[j+2] ++;
				}
				if(grade2 < cmp_grade3){
					R[i+1] ++;
				} else if (grade2 > cmp_grade3){
					R[j+2] ++;
				}
				if(grade3 < cmp_grade3){
					R[i+2] ++;
				} else if (grade3 > cmp_grade3){
					R[j+2] ++;
				}
				if(grade4 < cmp_grade3){
					R[i+3] ++;
				} else if (grade4 > cmp_grade3){
					R[j+2] ++;
				}

				float cmp_grade4 = F[j+3];
				if(grade1 < cmp_grade4){
					R[i] ++;
				} else if (grade1 > cmp_grade4){
					R[j+3] ++;
				}
				if(grade2< cmp_grade4){
					R[i+1] ++;
				} else if (grade2 > cmp_grade4){
					R[j+3] ++;
				}
				if(grade3 < cmp_grade4){
					R[i+2] ++;
				} else if (grade3 > cmp_grade4){
					R[j+3] ++;
				}
				if(grade4 < cmp_grade4){
					R[i+3] ++;
				} else if (grade4 > cmp_grade4){
					R[j+3] ++;
				}
			}
		}
		// deal with corner case that N is not a multiply of 4 for j
		while(j<N){
			float cmp_grade_left = F[j];
			if(grade1 < cmp_grade_left){
				R[i] ++;
			} else if (grade1 > cmp_grade_left){
				R[j] ++;
			}
			if(grade2< cmp_grade_left){
				R[i+1] ++;
			} else if (grade2 > cmp_grade_left){
				R[j] ++;
			}
			if(grade3 < cmp_grade_left){
				R[i+2] ++;
			} else if (grade3 > cmp_grade_left){
				R[j] ++;
			}
			if(grade4 < cmp_grade_left){
				R[i+3] ++;
			} else if (grade4 > cmp_grade_left){
				R[j] ++;
			}
			j++;
		}
		// record the grades of 4 students to average calculation
       	temp_avg = temp_avg + grade1 + grade2 + grade3 + grade4;	
		if (grade1 >= 50.0){
			temp_passing_avg += grade1;
			temp_num_passed ++;
		}
		if (grade2 >= 50.0){
			temp_passing_avg += grade2;
			temp_num_passed ++;
		}
		if (grade3 >= 50.0){
			temp_passing_avg += grade3;
			temp_num_passed ++;
		}
		if (grade4 >= 50.0){
			temp_passing_avg += grade4;
			temp_num_passed ++;
		}
    }
    // deal with the corner case that N is not a multiply of 4 for i
    while(i<N){
		grade1 = F[i];
		temp_avg += grade1;
		if (grade1 >= 50.0) {
   	        temp_passing_avg += grade1;
                temp_num_passed ++;
    	}
		for (j = i; j<N; j++){
			if(grade1 < F[j]){
					R[i] ++;
				} else if (grade1 > F[j]){
					R[j] ++;
				}
			
		}
		i++;
    }

    // check for div by 0
    if (N > 0) temp_avg /= N;
    if (temp_num_passed) temp_passing_avg /= temp_num_passed;

    *avg = temp_avg;
    *passing_avg = temp_passing_avg;
    *num_passed = temp_num_passed ;

} // compute_ranks




