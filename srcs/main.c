/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:02:24 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/05 17:04:19 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"

int main(void)
{
	char		*output;
	t_info		info;
	t_process	*processes;
	
	while (output = readline("test : "))
	{
		processes = first_split(output, &info);
		processing_instruction(processes, info.process_count);
		free(output);
	}
	return (0);
}

/*
info 구조체

typedef struct s_info
{
	명령어
	옵션
	인자
	리다이렉션 + 파일 (연결리스트)
}	t_info;
*/

//int	main (void)
//{
	// signal , 구조체 init
	//while (readline())
	//{
		// history 관리
		// split (파이프 기준으로)
		// 파이프 기준으로 반복 ->  parsing redirection 기준으로
		// 한번 더 쪼갠 상태에서 넘겨줄 수 있음)


//		어떤 기준으로(파이프) 잘라서
//		이차원 배열에 넣어준다.
//		삼차원 배열
//		[A][B][C]
//		[cat] [hello  !!  world] [> b] [> c]


//		echo aad asdf sadhle        "'"h"s"c"'" 안넘기고 넘기고 e e  e  e e hhhhelll
//		echo "-n"hello > a
//echo -n
//cd 경로

//export bash





		//개수만큼 반복
		//{
			// makepipe() 자식과 부모 간에 pipe 이어주는 파트   ////// pipe dup 
			// fork (자식 프로세스 등장)
			// 엄마는 자식에게 받기만 한다. [ close 주고 받는 안쓰는거 ] 엄마는 표준입력 (0) --> 받는 fd로 바꿔준다.
			// 자식 -> 엄마  [ 주기만 하는 자식의 fd (표준출력) 1 --> 엄마에게 보내는 fd로 바꿔준다 ]
		//}
	//}
//}
