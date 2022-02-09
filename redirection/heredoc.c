/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 23:25:54 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/09 23:25:57 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	heredoc(t_process *process)
{
	t_list	*temp;
	int		count;

	count = 0;
	temp = process->redirect;
	/*
		history에는 heredoc때 적었던 모든 글자가 저장된다.
		이거 history에 계속 업데이트 해줘야하나.
		여러줄이 history에 한번에 들어와야 하기 때문에
		size를 어떻게 관리해야할지 모르겠다.
		(직접 테스트 해보기를 바람 backspace 눌러 지우는 것 까지)

		arguments 가 존재할때는
		heredoc 으로 들어온 애들은
		종료 조건만 되고, 처리되지 않는다.
		cat a(파일이름) << aaa 등등 했을때
		결국 a 파일 내용만 출력

		cat 같이 PATH에서 쓰는 명령어에서
		arguments 가 없을때
		heredoc으로 들어온 애들은 전부 인자가 된다.

		build in 함수들은 입력을 받지 않기 때문에
		영향을 주지 못하는가?
		- export << aaa << bbb
		하면 heredoc이 종료 조건은 되지만
		결국 export 로 환경변수 목록만 출력된다.

		

		****현재 구상****
		arguments에 뭔가 있으면
		heredoc은 history만 신경 쓰면 되고,
		arguments에 넣어주면 안된다. (함수 실행 과정에서 영향을 줄 수 있음)
		그래서 따로 배열이나 머시깽이를 만들어서 저장만 해주고 (history를 위해)
		종료되면 그냥 평소처럼 함수 실행시키고 끝

		arguments에 뭔가 없으면
		heredoc에서 적은 애들 (뒤에서 두번째부터 그 영향 가는 애들만 << aaa << bbb 에서 aaa 와 bbb 사이에 적는 애들)
		arguments에 업데이트 계속 해줌
		근데 출력에는 영향 안가는 (<< aaa << bbb 에서 aaa 를 적기 전에 적는 애들)
		애들도 history에는 저장되어야 하기에 여전히 배열이나 머시깽이 만들어서 저장 해준다.


		==> 새로 배열같은거 만들어서 저장해줘야 하는 것은 동일 (history 위해서)
		==> arguments 유무에 따라서 업데이트 해준다 만다 차이.
	*/
}
